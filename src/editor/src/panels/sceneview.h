#pragma once

#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "imgui.h"
#include <imgui-SFML.h>

namespace Serum2D::Editor {
    class SceneHierarchyPanel;

    class SceneViewPanel {
    public:
        SceneViewPanel();

        void processEvent(sf::Event event);
        void update();
    private:
        void drawGridLines();

        float zoom = 1; // Zoom

        bool focus = false; // Is pane in focus
        bool moving = false; // Is currently moving

        sf::Vector2f oldPos;

        sf::RenderTexture renderTexture;
        sf::View sceneView;

        sf::RectangleShape gridLineY, gridLineX;

        friend SceneHierarchyPanel;
    };
}