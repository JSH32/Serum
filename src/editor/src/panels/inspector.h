#pragma once

#include "Serum/scene.h"
#include "Serum/entity.h"
#include "editorpanel.h"
#include "scenehierarchy.h"

namespace Serum2D::Editor {
    class InspectorPanel final : public EditorPanel {
    public:
        InspectorPanel(Core::Scene& scene, SceneHierarchyPanel* sceneHierarchy)
            : scene(scene), sceneHierarchy(sceneHierarchy) {}

        void onUpdate() override;
        Core::Scene& scene;
    private:
        static void twoColumnBegin(const std::string_view& label, float labelWidth);

        template<typename T, typename Fn>
        static void drawComponent(const std::string &name, Core::Entity entity, bool removable, Fn fn);

        SceneHierarchyPanel* sceneHierarchy;
    };
}