#include <cstring>
#include "inspector.h"
#include "imgui_internal.h"
#include "components/tag.h"
#include "components/shape.h"
#include "imgui_utils.h"

#include "icons.h"

namespace Serum2D::Editor {
    void InspectorPanel::OnUpdate() {
        ImGui::Begin(ICON_FA_INFO_CIRCLE " Inspector");
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
                ImGui::EndColumns();
            });

            DrawComponent<Core::Components::ShapeComponent>("Shape Renderer", sceneHierarchy->selectedObject, false, [](Core::Components::ShapeComponent& shape) {
                static const char* shapeTypeStrings[] = { "Rectangle", "Circle" };
                const char* current;

                if (shape.shapeType == Core::Components::ShapeType::Rectangle)
                    current = shapeTypeStrings[0];
                else if (shape.shapeType == Core::Components::ShapeType::Circle)
                    current = shapeTypeStrings[1];

                TwoColumnBegin("Shape type", 110);
                if (ImGui::BeginCombo("##Type", current)) {
                    if (ImGui::Selectable(shapeTypeStrings[0], shape.shapeType == Core::Components::ShapeType::Rectangle))
                        shape.SetShape(Core::Components::ShapeType::Rectangle);
                    if (ImGui::Selectable(shapeTypeStrings[1], shape.shapeType == Core::Components::ShapeType::Circle))
                        shape.SetShape(Core::Components::ShapeType::Circle);
                    ImGui::EndCombo();
                }
                ImGui::EndColumns();

                float color[4] = {
                    static_cast<float>(shape.shape->getFillColor().r) / 255.f,
                    static_cast<float>(shape.shape->getFillColor().g) / 255.f,
                    static_cast<float>(shape.shape->getFillColor().b) / 255.f,
                    static_cast<float>(shape.shape->getFillColor().a) / 255.f
                };

                TwoColumnBegin("Color", 110);
                if (ImGui::ColorEdit4("##Color", color))
                    shape.shape->setFillColor(sf::Color(
                            (int)(color[0] * 255.f),
                            (int)(color[1] * 255.f),
                            (int)(color[2] * 255.f),
                            (int)(color[3] * 255.f)));
                ImGui::EndColumns();

                TwoColumnBegin("Outline width", 110);
                float outlineThickness = shape.shape->getOutlineThickness();
                if (ImGui::DragFloat("##OutlineWidth", &outlineThickness, 0.1f, 0.0f, 0.0f, "%.2f"))
                    shape.shape->setOutlineThickness(outlineThickness);
                ImGui::EndColumns();

                float outlineColor[4] = {
                        static_cast<float>(shape.shape->getOutlineColor().r) / 255.f,
                        static_cast<float>(shape.shape->getOutlineColor().g) / 255.f,
                        static_cast<float>(shape.shape->getOutlineColor().b) / 255.f,
                        static_cast<float>(shape.shape->getOutlineColor().a) / 255.f
                };

                TwoColumnBegin("Outline color", 110);
                if (ImGui::ColorEdit4("##OutlineColor", outlineColor))
                    shape.shape->setOutlineColor(sf::Color(
                            (int)(outlineColor[0] * 255.f),
                            (int)(outlineColor[1] * 255.f),
                            (int)(outlineColor[2] * 255.f),
                            (int)(outlineColor[3] * 255.f)));
                ImGui::EndColumns();

                // Shape specific options
                if (shape.shapeType == Core::Components::ShapeType::Rectangle) {
                    if (ImGui::TreeNodeEx("Rectangle properties", ImGuiTreeNodeFlags_DefaultOpen)) {
                        auto* rect = dynamic_cast<sf::RectangleShape*>(shape.shape.get());
                        sf::Vector2f size = rect->getSize();
                        if (Vector2fEditor("Size", size, 70)) {
                            rect->setSize(size);
                            rect->setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
                        }
                        ImGui::TreePop();
                    }
                } else if (shape.shapeType == Core::Components::ShapeType::Circle) {
                    if (ImGui::TreeNodeEx("Circle properties", ImGuiTreeNodeFlags_DefaultOpen)) {
                        auto* circle = dynamic_cast<sf::CircleShape*>(shape.shape.get());
                        float radius = circle->getRadius();

                        TwoColumnBegin("Radius", 70);
                        if (ImGui::DragFloat("##Radius", &radius, 0.1f, 0.0f, 0.0f, "%.2f")) {
                            circle->setOrigin(sf::Vector2f(radius, radius));
                            circle->setRadius(radius);
                        }
                        ImGui::EndColumns();

                        TwoColumnBegin("Points", 70);
                        int pointCount = (int)circle->getPointCount();
                        if (ImGui::DragInt("##Points", &pointCount, 1.0f, 3, INT_MAX, "%d", ImGuiSliderFlags_AlwaysClamp))
                            circle->setPointCount(pointCount);
                        ImGui::EndColumns();

                        ImGui::TreePop();
                    }
                }
            });

            ImGui::Separator();
            if (ImGui::Button(ICON_FA_PLUS_SQUARE_O " Add Component", ImVec2(ImGui::GetContentRegionAvailWidth(), 25)))
                ImGui::OpenPopup("AddComponent");

            if (ImGui::BeginPopup("AddComponent")) {
                bool hadShapeComponent = false;
                if (sceneHierarchy->selectedObject.hasComponent<Core::Components::ShapeComponent>()) {
                    ImGui::BeginDisabled();
                    hadShapeComponent = true;
                }

                if (ImGui::MenuItem("Shape renderer"))
                    sceneHierarchy->selectedObject.addComponent<Core::Components::ShapeComponent>(Core::Components::ShapeType::Rectangle);

                if (hadShapeComponent)
                    ImGui::EndDisabled();

                ImGui::EndPopup();
            }
//            ImGui::PopItemWidth();
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

            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0, 0, 0));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));
            if (ImGui::Button(ICON_FA_COG, ImVec2{ lineHeight, lineHeight }))
                ImGui::OpenPopup("ComponentSettings");
            ImGui::PopStyleColor(3);

            bool removeComponent = false;
            if (ImGui::BeginPopup("ComponentSettings")) {
                if (ImGui::MenuItem("Remove component"))
                    removeComponent = true;

                ImGui::EndPopup();
            }

            if (open) {
                fn(component);
                ImGui::TreePop();
            }

            if (removeComponent)
                entity.removeComponent<T>();
        }
    }

    bool InspectorPanel::Vector2fEditor(const std::string& label, sf::Vector2f& vec, float labelWidth) {
        bool changed = false;

        ImGui::PushID(label.c_str());

        // Render label name in front of values
        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, labelWidth);
        ImGui::Text("%s", label.c_str());
        ImGui::NextColumn();

        // For some reason GetContentRegionAvailWidth goes over the actual available content width by about 33
        ImGui::PushMultiItemsWidths(2, ImGui::GetContentRegionAvailWidth() - 33);
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 2, 5 });

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::SetNextItemWidth(7);
        if (ImGui::Button("X")) {
            vec.x = 0.0f;
            changed = true;
        }
        ImGui::PopStyleColor(3);
        ImGui::SameLine();
        if (ImGui::DragFloat("##X", &vec.x, 0.1f, 0.0f, 0.0f, "%.2f"))
            changed = true;
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
        ImGui::SetNextItemWidth(7);
        if (ImGui::Button("Y")) {
            vec.y = 0.0f;
            changed = true;
        }
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        if (ImGui::DragFloat("##Y", &vec.y, 0.1f, 0.0f, 0.0f, "%.2f"))
            changed = true;
        ImGui::PopItemWidth();
        ImGui::PopStyleVar();
        ImGui::EndColumns();
        ImGui::PopID();

        return changed;
    }

    void InspectorPanel::TwoColumnBegin(const std::string_view& label, float labelWidth) {
        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, labelWidth);
        ImGui::Text("%s", label.data());
        ImGui::NextColumn();
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvailWidth());
    }
}
