#include "Converter.h"

namespace Serum::UI {
    ImVec4 Converter::ToImVec4(const Color &color) {
        return ImVec4(color.r, color.g, color.b, color.a);
    }

    Color Converter::ToColor(const ImVec4 &color) {
        return Color(color.x, color.y, color.z, color.w);
    }

    ImVec2 Converter::ToImVec2(const glm::vec2 &pos) {
        return ImVec2(pos.x, pos.y);
    }

    glm::vec2 Converter::ToVec2(const ImVec2 &pos) {
        return glm::vec2(pos.x, pos.y);
    }
}