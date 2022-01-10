// ReSharper disable CppInconsistentNaming
#include "imgui_utils.h"

#include <imgui_internal.h>

namespace ImGui {
    std::vector<float> alphas;

    void PushDisabled(const bool disabled) {
        alphas.push_back(GetStyle().Alpha);
        GetStyle().Alpha = disabled ? 0.25f : 1.0f;
    }

    void PopDisabled(int num) {
        while (num--) {
            GetStyle().Alpha = alphas.back();
            alphas.pop_back();
        }
    }

    std::tuple<ImVec2, ImVec2> GetContentArea() {
        return {
                {ImGui::GetWindowContentRegionMin().x + ImGui::GetWindowPos().x,
                 ImGui::GetWindowContentRegionMax().y + ImGui::GetWindowPos().y},
                {ImGui::GetWindowContentRegionMax().x + ImGui::GetWindowPos().x,
                 ImGui::GetWindowContentRegionMin().y + ImGui::GetWindowPos().y}
        };
    }

    sf::Vector2f CalculateImOffset(const  sf::RenderTarget& target, const  sf::Vector2i pos, const ImVec2 contentStartPos) {
        return target.mapPixelToCoords(sf::Vector2i(
                (int)((float)pos.x - contentStartPos.x),
                (int)((-(float)pos.y) + contentStartPos.y)));
    }

    bool Vector2fEditor(const std::string& label, sf::Vector2f& vec, const float labelWidth) {
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
}