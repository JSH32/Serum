#pragma once

#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "imgui.h"
#include "editorpanel.h"
#include "Serum/scene.h"
#include "Serum/entity.h"

namespace Serum2D::Editor {
    class SceneHierarchyPanel;

    class SceneViewPanel final : public EditorPanel {
    public:
        SceneViewPanel(Core::Scene* scene, Core::Entity& selectedEntity);

        void onEvent(sf::Event event) override;
        void onUpdate() override;
    private:
        void drawGridLines();

        /**
         * Draw the position gizmo
         */
        void updateTransformPositionGizmo(const sf::Transformable& transform);

        /**
         * Draw the scale gizmo
         */
        void updateTransformScaleGizmo(const sf::Transformable& transform);

        float zoom = 1; // Zoom
        bool panning = false; // Is currently panning camera

        sf::Vector2f oldPos;

        sf::RenderTexture renderTexture;
        sf::View sceneView;

        sf::RectangleShape gridLineY, gridLineX;

        enum class TransformType {
            None, // Default when not doing anything
            Position,
            Scale,
            Rotate
        };

        enum class DragAxis {
            Horizontal,
            Vertical,
            Any
        };

        bool transforming = false;
        DragAxis dragAxis = DragAxis::Horizontal;
        TransformType transformType = TransformType::Position;
        sf::Vector2f oldItemPos;

        // Only used for position and scale
        sf::FloatRect xGizmoBounding, yGizmoBounding, anyBounding;

        // Position of window content
        std::tuple<ImVec2, ImVec2> windowContentArea;

        Core::Entity& selectedEntity;
        Core::Scene* scene;

        const inline static sf::Color widgetGreen = sf::Color(206, 255, 189, 255);
        const inline static sf::Color widgetRed = sf::Color(255, 86, 92, 255);
        const inline static sf::Color widgetBlue = sf::Color(88, 87, 255, 255);

        friend SceneHierarchyPanel;
    };
}