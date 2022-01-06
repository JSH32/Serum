#pragma once

#include "scene.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "entity.h"
#include "sceneview.h"

namespace Serum2D::Editor {
    class SceneHierarchyPanel : public EditorPanel {
    public:
        SceneHierarchyPanel(Core::Scene& scene, SceneViewPanel* sceneViewPanel)
            : scene(scene), sceneViewPanel(sceneViewPanel) {};
//        void update();
//        void processEvent(sf::Event event);

        void onEvent(sf::Event event) override;
        void onUpdate() override;

        Core::Scene& scene;
        Core::Entity selectedObject;
    private:
        void drawEntity(Core::Entity entity);
        SceneViewPanel* sceneViewPanel;
    };
}