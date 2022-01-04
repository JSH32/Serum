#pragma once

#include "scene.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "entity.h"
#include "sceneview.h"

namespace Serum2D::Editor {
    class SceneHierarchyPanel {
    public:
        explicit SceneHierarchyPanel(Core::Scene& scene, SceneViewPanel& sceneViewPanel)
            : scene(scene), sceneViewPanel(sceneViewPanel) {};
        void update();
        void processEvent(sf::Event event);

        Core::Scene& scene;

        Core::Entity selectedObject;
    private:
        static void vector2fEditor(const std::string& label, sf::Vector2f& vec);
        void drawEntity(Core::Entity entity);
        bool focus = false;
        SceneViewPanel& sceneViewPanel;

        template<typename T, typename Function>
        static void DrawComponent(const std::string &name, Core::Entity entity, Function uiFunction);
    };
}