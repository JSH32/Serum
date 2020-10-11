#pragma

#include "Serum/pch.h"

#include "WindowProps.h"

// Events
#include "Serum/Core/Event/Event.h"
#include "Serum/Core/Event/ApplicationEvent.h"
#include "Serum/Core/Event/MouseEvent.h"
#include "Serum/Core/Event/KeyEvent.h"

namespace Serum {
    class Window {
    public:
        Window(const WindowProps& props);
        ~Window();

        void Update();

        uint GetWidth() {}
        uint GetHeight() {}

        void SetEventCallback(const EventCallbackFn& callback) { data.EventCallback = callback; }
        void SetVSync(bool enabled);
        bool IsVSync();

        void SetCallbacks();

        GLFWwindow* GetWindow() const { return window; }
    private:
        GLFWwindow* window;
        WindowData data;
    };
}