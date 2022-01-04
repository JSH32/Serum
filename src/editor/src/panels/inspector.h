#pragma once

#include "scene.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "entity.h"
#include "editorpanel.h"
#include "scenehierarchy.h"

namespace Serum2D::Editor {
    class InspectorPanel : public EditorPanel {
    public:
        InspectorPanel(Core::Scene& scene, SceneHierarchyPanel* sceneHierarchy)
            : scene(scene), sceneHierarchy(sceneHierarchy) {};

        void OnEvent(sf::Event event) override;
        void OnUpdate() override;

        Core::Scene& scene;
    private:
        static void Vector2fEditor(const std::string& label, sf::Vector2f& vec);

        template<typename T, typename Fn>
        static void DrawComponent(const std::string &name, Core::Entity entity, bool removable, Fn fn);

        SceneHierarchyPanel* sceneHierarchy;
    };
}