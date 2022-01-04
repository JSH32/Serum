#include <cstring>
#include "scenehierarchy.h"
#include "entity.h"
#include "components/tag.h"
#include "SFML/Graphics/Transformable.hpp"
#include "imgui_internal.h"
#include "SFML/Window/Event.hpp"

static const ImGuiTreeNodeFlags TREENODE_FLAGS =
        ImGuiTreeNodeFlags_DefaultOpen |
        ImGuiTreeNodeFlags_FramePadding |
        ImGuiTreeNodeFlags_OpenOnArrow |
        ImGuiTreeNodeFlags_SpanAvailWidth;

namespace Serum2D::Editor {
    void SceneHierarchyPanel::drawEntity(Core::Entity entity) {
        auto tag = entity.getComponent<Core::Components::TagComponent>();

        auto treeNode = TREENODE_FLAGS;
        if (entity == selectedObject)
            treeNode = TREENODE_FLAGS | ImGuiTreeNodeFlags_Selected;

        if (ImGui::TreeNodeEx((void *) (uint64_t) (uint32_t) entity, treeNode, "%s", tag.tag.c_str())) {
            if (ImGui::IsItemClicked(0)) {
                selectedObject = entity;
            }

            ImGui::TreePop();
        }

        if (ImGui::BeginPopupContextItem()) {
            if (ImGui::MenuItem("Delete")) {
                scene.destroyEntity(entity);
                if (selectedObject == entity)
                    selectedObject = {};
            }

            ImGui::EndPopup();
        }
    }

    void SceneHierarchyPanel::OnEvent(sf::Event event) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::F) {
                sceneViewPanel->sceneView.setCenter(selectedObject.getComponent<sf::Transformable>().getPosition());
                sceneViewPanel->renderTexture.setView(sceneViewPanel->sceneView);
            }
        }
    }

    void SceneHierarchyPanel::OnUpdate() {
        ImGui::Begin("Hierarchy");
        scene.registry.each([&](auto entityID) {
            Core::Entity entity{ entityID , &scene };
            drawEntity(entity);
        });

        if (ImGui::BeginPopupContextWindow(nullptr, 1, false)) {
            if (ImGui::MenuItem("Create New Entity"))
                scene.createEntity("New Entity");

            ImGui::EndPopup();
        }

        ShouldReceiveEvents(ImGui::IsWindowFocused());

        ImGui::End();

//
//        ImGui::Begin("Properties");
//        if (selectedObject) {
//            if (selectedObject.hasComponent<Core::Components::TagComponent>()) {
//                auto& tag = selectedObject.getComponent<Core::Components::TagComponent>().tag;
//
//                char buffer[256];
//                memset(buffer, 0, sizeof(buffer));
//                std::strncpy(buffer, tag.c_str(), sizeof(buffer));
//                if (ImGui::InputText("##Name", buffer, sizeof(buffer)))
//                    tag = std::string(buffer);
//            }
//
//            if (selectedObject.hasComponent<sf::Transformable>()) {
//                DrawComponent<sf::Transformable>("Transform", selectedObject, [](auto& transform) {
//                    sf::Vector2f position = transform.getPosition();
//                    vector2fEditor("Position", position);
//                    transform.setPosition(position);
//
//                    sf::Vector2f scale = transform.getScale();
//                    vector2fEditor("Scale", scale);
//                    transform.setScale(scale);
//
//                    float rotation = transform.getRotation();
//
//                    ImGui::Columns(2);
//                    ImGui::SetColumnWidth(0, 100);
//                    ImGui::Text("Rotation");
//                    ImGui::NextColumn();
//
//                    ImGui::PushItemWidth(ImGui::GetContentRegionAvailWidth());
//                    if (ImGui::DragFloat("##Rotation", &rotation, 0.1f, 0.0f, 0.0f, "%.2f"))
//                        transform.setRotation(rotation);
//                    ImGui::PopItemWidth();
//                });
//            }
//        }
    }
}
