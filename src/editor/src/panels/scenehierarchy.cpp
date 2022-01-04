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
    void SceneHierarchyPanel::update() {
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

        focus = ImGui::IsWindowFocused();
        ImGui::End();

        ImGui::Begin("Properties");
        if (selectedObject) {
            if (selectedObject.hasComponent<Core::Components::TagComponent>()) {
                auto& tag = selectedObject.getComponent<Core::Components::TagComponent>().tag;

                char buffer[256];
                memset(buffer, 0, sizeof(buffer));
                std::strncpy(buffer, tag.c_str(), sizeof(buffer));
                if (ImGui::InputText("##Name", buffer, sizeof(buffer)))
                    tag = std::string(buffer);
            }

            if (selectedObject.hasComponent<sf::Transformable>()) {
                DrawComponent<sf::Transformable>("Transform", selectedObject, [](auto& transform) {
                    sf::Vector2f position = transform.getPosition();
                    vector2fEditor("Position", position);
                    transform.setPosition(position);

                    sf::Vector2f scale = transform.getScale();
                    vector2fEditor("Scale", scale);
                    transform.setScale(scale);

                    float rotation = transform.getRotation();

                    ImGui::Columns(2);
                    ImGui::SetColumnWidth(0, 100);
                    ImGui::Text("Rotation");
                    ImGui::NextColumn();

                    if (ImGui::DragFloat("##Rotation", &rotation, 0.1f, 0.0f, 0.0f, "%.2f"))
                        transform.setRotation(rotation);
                });
            }
        }

        ImGui::End();
    }

    void SceneHierarchyPanel::drawEntity(Core::Entity entity) {
        auto tag = entity.getComponent<Core::Components::TagComponent>();

        auto treeNode = TREENODE_FLAGS;
        if (entity == selectedObject)
            treeNode = TREENODE_FLAGS | ImGuiTreeNodeFlags_Selected;

        if (ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, treeNode, "%s", tag.tag.c_str())) {
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

    void SceneHierarchyPanel::vector2fEditor(const std::string& label, sf::Vector2f& vec) {
        ImGui::PushID(label.c_str());

        // Render label name in front of values
        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, 100);
        ImGui::Text("%s", label.c_str());

        ImGui::NextColumn();

        ImGui::PushMultiItemsWidths(2, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        if (ImGui::Button("X"))
            vec.x = 0.0f;
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##X", &vec.x, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
        if (ImGui::Button("Y"))
            vec.y = 0.0f;
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##Y", &vec.y, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();

        ImGui::PopStyleVar();
        ImGui::PopID();
        ImGui::NextColumn();
    }

    void SceneHierarchyPanel::processEvent(sf::Event event) {
        if (!focus) return;

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::F) {
                sceneViewPanel.sceneView.setCenter(selectedObject.getComponent<sf::Transformable>().getPosition());
                sceneViewPanel.renderTexture.setView(sceneViewPanel.sceneView);
            }
        }
    }

    template<typename T, typename Function>
    void SceneHierarchyPanel::DrawComponent(const std::string& name, Core::Entity entity, Function uiFunction) {
        const ImGuiTreeNodeFlags treeNodeFlags =
                ImGuiTreeNodeFlags_DefaultOpen |
                ImGuiTreeNodeFlags_Framed |
                ImGuiTreeNodeFlags_SpanAvailWidth |
                ImGuiTreeNodeFlags_AllowItemOverlap |
                ImGuiTreeNodeFlags_FramePadding;

        if (entity.hasComponent<T>()) {
            auto& component = entity.getComponent<T>();
            ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
            float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
            ImGui::Separator();
            bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, name.c_str());
            ImGui::PopStyleVar();

            ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
            if (ImGui::Button("+", ImVec2{ lineHeight, lineHeight })) {
                ImGui::OpenPopup("ComponentSettings");
            }

//            bool removeComponent = false;
//            if (ImGui::BeginPopup("ComponentSettings")) {
//                if (ImGui::MenuItem("Remove component"))
//                    removeComponent = true;
//
//                ImGui::EndPopup();
//            }

            if (open) {
                uiFunction(component);
                ImGui::TreePop();
            }
//
//            if (removeComponent)
//                entity.removeComponent<T>();
        }
    }
}
