#pragma once

#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "imgui.h"
#include "editorpanel.h"
#include "scene.h"
#include <imgui-SFML.h>

namespace Serum2D::Editor {
    class SceneHierarchyPanel;

    class SceneViewPanel : public EditorPanel {
    public:
        explicit SceneViewPanel(Core::Scene* scene);

        void onEvent(sf::Event event) override;
        void onUpdate() override;
    private:
        void drawGridLines();

        float zoom = 1; // Zoom
        bool moving = false; // Is currently moving

        sf::Vector2f oldPos;

        sf::RenderTexture renderTexture;
        sf::View sceneView;

        sf::RectangleShape gridLineY, gridLineX;
        Core::Scene* scene;

        friend SceneHierarchyPanel;
    };
}