#pragma once

#include "scene.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "entity.h"

namespace Serum2D::Editor {
    class InspectorPanel {
    public:
        explicit InspectorPanel(Core::Scene& scene) : scene(scene) {};
        void update();

        Core::Scene& scene;
    private:
        Core::Entity selectedObject;
    };
}