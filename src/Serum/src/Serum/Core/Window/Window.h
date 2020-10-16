#pragma once

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
        explicit Window(const WindowProps& props);
        ~Window();

        void Update();

        uint GetWidth() { return data.Height; }
        uint GetHeight() { return data.Width; }

        void SetEventCallback(const EventCallbackFn& callback) { data.EventCallback = callback; }
        void SetVSync(bool enabled);
        bool IsVSync() const;

        void SetCallbacks();

        GLFWwindow* GetWindow() const { return window; }
    private:
        GLFWwindow* window;
        WindowData data;
    };
}