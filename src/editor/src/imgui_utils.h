#pragma once

#include <vector>
#include <imgui.h>

/**
 * Things inserted into the ImGui namespace, addon functions or utilities
 */
namespace ImGui {
    std::vector<float> alphas;

    void PushDisabled(bool disabled = true) {
        alphas.push_back(GetStyle().Alpha);
        GetStyle().Alpha = disabled ? 0.25f : 1.0f;
    }

    void PopDisabled(int num = 1) {
        while (num--) {
            GetStyle().Alpha = alphas.back();
            alphas.pop_back();
        }
    }
}
