#pragma once

#include "Serum/scene.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "Serum/entity.h"
#include "sceneview.h"

namespace Serum2D::Editor {
    class SceneHierarchyPanel : public EditorPanel {
    public:
        SceneHierarchyPanel(Core::Scene& scene, SceneViewPanel* sceneViewPanel, Core::Entity& selectedEntity)
            : scene(scene), sceneViewPanel(sceneViewPanel), selectedEntity(selectedEntity) {};

        void onEvent(sf::Event event) override;
        void onUpdate() override;

        Core::Scene& scene;
        Core::Entity& selectedEntity;
    private:
        void drawEntity(Core::Entity entity);
        SceneViewPanel* sceneViewPanel;
    };
}