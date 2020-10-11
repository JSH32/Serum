#include "Application.h"

namespace Serum {
    void Application::OnWindowClose(WindowCloseEvent &e) {
        running = false;
    }

    void Application::Close() {
        running = false;
    }

    void Application::OnEvent(Event& e) {
        EventDispatcher dispatch(e);

        dispatch.Dispatch<WindowCloseEvent>(BIND_FN(OnWindowClose));
    }

    void Application::Run() {
        while(running) {
            this->deltaTime = (float)glfwGetTime() - deltaTime;

            window->Update();
        }
    }

    Application::Application(const std::string &name) {
        this->window = std::make_unique<Window>(WindowProps(name));

        window->SetEventCallback(BIND_FN(OnEvent));
    }
}