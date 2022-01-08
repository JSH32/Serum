#pragma once

#include <vector>
#include <imgui.h>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

/**
 * Things inserted into the ImGui namespace, addon functions or utilities
 */
namespace ImGui {
    void PushDisabled(bool disabled = true);
    void PopDisabled(int num = 1);

    /**
     * Get the position of the content area top and bottom corner
     * @return
     */
    std::tuple<ImVec2, ImVec2> GetContentArea();

    /**
     * Calculate position on RenderTarget based on offset
     *
     * @param target RenderTarget to map to coordinate point
     * @param pos Position relative to window
     * @param contentStartPos Starting content position, click position will be relative to this point at (0, 0)
     */
    sf::Vector2f CalculateImOffset(sf::RenderTarget& target, sf::Vector2i pos, ImVec2 contentStartPos);
    bool Vector2fEditor(const std::string& label, sf::Vector2f& vec, float labelWidth = 100.f);
}