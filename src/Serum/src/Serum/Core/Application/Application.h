#pragma once

#include "Serum/Core/Event/Event.h"
#include "Serum/Core/Window/Window.h"
#include "Serum/Core/Event/ApplicationEvent.h"

namespace Serum {
class Application {
    public:
        explicit Application(const std::string& name = "Serum");
        virtual ~Application() = default;

        void OnEvent(Event& e);

        void Close();

        Window& GetWindow() { return *window; }

        void Run();
    private:
        void OnWindowClose(WindowCloseEvent& e);
        void OnWindowResize(WindowResizeEvent& e);

        bool running = true;

        float deltaTime = 0.0f;

        std::unique_ptr<Window> window;
    };
}