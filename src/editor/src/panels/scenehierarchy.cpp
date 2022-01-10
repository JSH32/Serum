#include "scenehierarchy.h"

#include "Serum/entity.h"
#include "Serum/components/entityinfo.h"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Window/Event.hpp"
#include "icons.h"


namespace Serum2D::Editor {
    void SceneHierarchyPanel::drawEntity(Core::Entity entity) const {
	    const auto& entityInfo = entity.getComponent<Core::Components::EntityInfoComponent>();

        constexpr ImGuiTreeNodeFlags treeNodeFlags =
            ImGuiTreeNodeFlags_DefaultOpen |
            ImGuiTreeNodeFlags_FramePadding |
            ImGuiTreeNodeFlags_OpenOnArrow |
            ImGuiTreeNodeFlags_SpanAvailWidth;

        auto treeNode = treeNodeFlags;
        if (entity == selectedEntity)
            treeNode = treeNodeFlags | ImGuiTreeNodeFlags_Selected;

        // Darken if disabled
        if (!entityInfo.enabled)
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.5f);

        if (ImGui::TreeNodeEx((void *) (uint64_t) (uint32_t) entity, treeNode, ICON_FA_CUBE " %s", entityInfo.tag.c_str())) {
            if (ImGui::IsItemClicked(0))
                selectedEntity = entity;

            ImGui::TreePop();
        }

        if (!entityInfo.enabled) ImGui::PopStyleVar();

        if (ImGui::BeginPopupContextItem()) {
            if (ImGui::MenuItem("Delete")) {
                scene.destroyEntity(entity);
                if (selectedEntity == entity)
                    selectedEntity = {};
            }

            ImGui::EndPopup();
        }
    }

    void SceneHierarchyPanel::onEvent(const sf::Event event) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::F && selectedEntity) {
                sceneViewPanel->sceneView.setCenter(selectedEntity.getComponent<sf::Transformable>().getPosition());
                sceneViewPanel->renderTexture.setView(sceneViewPanel->sceneView);
            }
        }
    }

    void SceneHierarchyPanel::onUpdate() {
        ImGui::Begin(ICON_FA_LIST_UL " Hierarchy");

        for (auto& entity : scene.getRootOrderedEntities())
        	drawEntity(entity);

        if (ImGui::BeginPopupContextWindow(nullptr, 1, false)) {
            if (ImGui::MenuItem("Create New Entity"))
                scene.createEntity("New Entity");

            ImGui::EndPopup();
        }

        setReceiveEvents(ImGui::IsWindowFocused());

        ImGui::End();
    }
}
