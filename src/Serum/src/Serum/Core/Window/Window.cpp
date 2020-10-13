#include "Window.h"

#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>

namespace Serum {
    static void GLFWErrorCallback(int error, const char* description) {
        std::cout << description << std::endl;
        exit(error);
    }

    Window::Window(const WindowProps &props) {
        this->data.Title = props.Title;
        this->data.Width = props.Width;
        this->data.Height = props.Height;

        glfwSetErrorCallback(GLFWErrorCallback);
        if (!glfwInit())
            exit(1);

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        window = glfwCreateWindow((int)props.Width, (int)props.Height, data.Title.c_str(), nullptr, nullptr);
        if (!window)
            exit(1);

        bgfx::renderFrame();

        bgfx::Init init;
        init.platformData.ndt = glfwGetX11Display();
        init.platformData.nwh = (void*)(uintptr_t)glfwGetX11Window(window);

        init.resolution.width = (uint32_t)data.Width;
        init.resolution.height = (uint32_t)data.Height;
        init.resolution.reset = BGFX_RESET_VSYNC;
        if (!bgfx::init(init))
            exit(1);

        const bgfx::ViewId kClearView = 0;
        bgfx::setViewClear(kClearView, BGFX_CLEAR_COLOR);
        bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);

        glfwSetWindowUserPointer(window, &data);

        SetCallbacks();

        bgfx::setDebug(BGFX_DEBUG_TEXT);
    }

    Window::~Window() {
        bgfx::shutdown();
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Window::Update() {
        glfwPollEvents();

        bgfx::reset(this->data.Width, this->data.Height, BGFX_RESET_VSYNC);
        bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);

        bgfx::touch(0);

        bgfx::dbgTextClear();

        bgfx::dbgTextPrintf(1, 1, 0x0f, "Hello World!");

        bgfx::frame();
    }

    void Window::SetVSync(bool enabled) {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        data.VSync = enabled;
    }

    bool Window::IsVSync() {
        return data.VSync;
    }

    void Window::SetCallbacks() {
        glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;

            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action) {
                case GLFW_PRESS: {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT: {
                    KeyPressedEvent event(key, 1);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int keycode) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            KeyTypedEvent event(keycode);
            data.EventCallback(event);
        });

        glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action) {
                case GLFW_PRESS: {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xPos, (float)yPos);
            data.EventCallback(event);
        });
    }
}