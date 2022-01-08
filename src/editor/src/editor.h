#pragma once

#include "SFML/Window/Window.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include "panels/sceneview.h"
#include "panels/scenehierarchy.h"

namespace Serum2D::Editor {
    class Editor {
    public:
        explicit Editor(sf::RenderWindow& window);

        void run();
        void onEvent(sf::Event event);
        void update();
    private:
        static void startDockSpace();

        std::vector<std::unique_ptr<EditorPanel>> panels;
        sf::RenderWindow& window;
        sf::Clock deltaTime;
    private:
        friend EditorPanel;

        Core::Scene scene;
        Core::Entity selectedEntity;
    };
}