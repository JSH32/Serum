#include "scenehierarchy.h"
#include "entity.h"
#include "components/entity_info.h"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Window/Event.hpp"
#include "icons.h"

static const ImGuiTreeNodeFlags TREENODE_FLAGS =
        ImGuiTreeNodeFlags_DefaultOpen |
        ImGuiTreeNodeFlags_FramePadding |
        ImGuiTreeNodeFlags_OpenOnArrow |
        ImGuiTreeNodeFlags_SpanAvailWidth;

namespace Serum2D::Editor {
    void SceneHierarchyPanel::drawEntity(Core::Entity entity) {
        auto& eInfo = entity.getComponent<Core::Components::EntityInfoComponent>();

        auto treeNode = TREENODE_FLAGS;
        if (entity == selectedObject)
            treeNode = TREENODE_FLAGS | ImGuiTreeNodeFlags_Selected;

        // Darken if disabled
        if (!eInfo.enabled)
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.5f);

        if (ImGui::TreeNodeEx((void *) (uint64_t) (uint32_t) entity, treeNode, ICON_FA_CUBE " %s", eInfo.tag.c_str())) {
            if (ImGui::IsItemClicked(0))
                selectedObject = entity;

            ImGui::TreePop();
        }

        if (!eInfo.enabled) ImGui::PopStyleVar();

        if (ImGui::BeginPopupContextItem()) {
            if (ImGui::MenuItem("Delete")) {
                scene.destroyEntity(entity);
                if (selectedObject == entity)
                    selectedObject = {};
            }

            ImGui::EndPopup();
        }
    }

    void SceneHierarchyPanel::onEvent(sf::Event event) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::F) {
                sceneViewPanel->sceneView.setCenter(selectedObject.getComponent<sf::Transformable>().getPosition());
                sceneViewPanel->renderTexture.setView(sceneViewPanel->sceneView);
            }
        }
    }

    void SceneHierarchyPanel::onUpdate() {
        ImGui::Begin(ICON_FA_LIST_UL " Hierarchy");
        scene.registry.each([&](auto entityID) {
            Core::Entity entity{ entityID , &scene };
            drawEntity(entity);
        });

        if (ImGui::BeginPopupContextWindow(nullptr, 1, false)) {
            if (ImGui::MenuItem("Create New Entity"))
                scene.createEntity("New Entity");

            ImGui::EndPopup();
        }

        setReceiveEvents(ImGui::IsWindowFocused());

        ImGui::End();
    }
}
