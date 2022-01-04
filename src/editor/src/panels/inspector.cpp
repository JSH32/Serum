#include <cstring>
#include <iostream>
#include "inspector.h"
#include "imgui_internal.h"
#include "components/tag.h"
#include "components/shape.h"

namespace Serum2D::Editor {

    void InspectorPanel::OnEvent(sf::Event event) {

    }

    void InspectorPanel::OnUpdate() {
        ImGui::Begin("Inspector");
        if (sceneHierarchy->selectedObject) {
            if (sceneHierarchy->selectedObject.hasComponent<Core::Components::TagComponent>()) {
                auto& tag = sceneHierarchy->selectedObject.getComponent<Core::Components::TagComponent>().tag;

                char buffer[256];
                memset(buffer, 0, sizeof(buffer));
                std::strncpy(buffer, tag.c_str(), sizeof(buffer));
                if (ImGui::InputText("Name##Name", buffer, sizeof(buffer)))
                    tag = std::string(buffer);
            }

            DrawComponent<sf::Transformable>("Transform", sceneHierarchy->selectedObject, false, [](auto& transform) {
                sf::Vector2f position = transform.getPosition();
                Vector2fEditor("Position", position);
                transform.setPosition(position);

                sf::Vector2f scale = transform.getScale();
                Vector2fEditor("Scale", scale);
                transform.setScale(scale);

                float rotation = transform.getRotation();

                ImGui::Columns(2);
                ImGui::SetColumnWidth(0, 100);
                ImGui::Text("Rotation");
                ImGui::NextColumn();

                ImGui::PushItemWidth(ImGui::GetContentRegionAvailWidth());
                if (ImGui::DragFloat("##Rotation", &rotation, 0.1f, 0.0f, 0.0f, "%.2f"))
                    transform.setRotation(rotation);
                ImGui::PopItemWidth();
                ImGui::EndColumns();
            });

            DrawComponent<Core::Components::ShapeComponent>("Shape Renderer", sceneHierarchy->selectedObject, false, [](Core::Components::ShapeComponent& shape) {
                static float color[4] = {
                        static_cast<float>(shape.GetFillColor().r),
                        static_cast<float>(shape.GetFillColor().g),
                        static_cast<float>(shape.GetFillColor().b),
                        static_cast<float>(shape.GetFillColor().a)};

                std::cout << color[0] << std::endl;
                if (ImGui::ColorEdit4("Color", color, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_DisplayRGB))
                    shape.SetFillColor(sf::Color((int)color[0], (int)color[1], (int)color[2], 255));
            });
        }
        ImGui::End();
    }

    template<typename T, typename Fn>
    void InspectorPanel::DrawComponent(const std::string &name, Core::Entity entity, bool removable, Fn fn) {
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
            bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, "%s", name.c_str());
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
                fn(component);
                ImGui::TreePop();
            }
//
//            if (removeComponent)
//                entity.removeComponent<T>();
        }
    }

    void InspectorPanel::Vector2fEditor(const std::string& label, sf::Vector2f& vec) {
        ImGuiIO& io = ImGui::GetIO();
        auto boldFont = io.Fonts->Fonts[0];
        ImGui::PushID(label.c_str());

        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0);

        // Render label name in front of values
        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, 100);
        ImGui::Text("%s", label.c_str());
        ImGui::NextColumn();

        ImGui::PushMultiItemsWidths(2, ImGui::GetContentRegionAvailWidth() - 25);
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

        float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::PushFont(boldFont);
        if (ImGui::Button("X"))
            vec.x = 0.0f;
        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##X", &vec.x, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
        ImGui::PushFont(boldFont);
        if (ImGui::Button("Y"))
            vec.y = 0.0f;
        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##Y", &vec.y, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();

        ImGui::PopStyleVar(2);

        ImGui::EndColumns();

        ImGui::PopID();
    }
}
