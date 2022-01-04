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

        Core::Scene scene;
        SceneViewPanel sceneViewPanel;
        SceneHierarchyPanel sceneHierarchyPanel;

        sf::RenderWindow& window;
        sf::Clock deltaTime;
    };
}