#pragma once

#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Window.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "imgui.h"
#include "editorpanel.h"
#include "Serum/scene.h"
#include <imgui-SFML.h>
#include "Serum/entity.h"
#include "Thor/Shapes/Arrow.hpp"
#include "imgui_utils.h"
#include "Serum/components/shape.h"

namespace Serum2D::Editor {
    class SceneHierarchyPanel;

    class SceneViewPanel : public EditorPanel {
    public:
        SceneViewPanel(Core::Scene* scene, Core::Entity& selectedEntity);

        void onEvent(sf::Event event) override;
        void onUpdate() override;
    private:
        void drawGridLines();

        float zoom = 1; // Zoom
        bool panning = false; // Is currently panning camera

        sf::Vector2f oldPos;

        sf::RenderTexture renderTexture;
        sf::View sceneView;

        sf::RectangleShape gridLineY, gridLineX;

        enum TransformType {
            None, // Default when not doing anything
            Position,
            Scale,
            Rotate
        };

        enum DragAxis {
            Horizontal,
            Vertical,
            Any
        };

        DragAxis dragAxis = DragAxis::Horizontal;
        bool transforming = false;
        TransformType transformType = TransformType::None;
        sf::Vector2f oldItemPos;

        // Only used for position and scale
        sf::FloatRect xGizmoBounding, yGizmoBounding, anyBounding;

        // Position of window content
        std::tuple<ImVec2, ImVec2> windowContentArea;

        Core::Entity& selectedEntity;
        Core::Scene* scene;

        friend SceneHierarchyPanel;
    };
}