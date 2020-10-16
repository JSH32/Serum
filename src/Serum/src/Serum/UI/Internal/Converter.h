#pragma once

#include "Serum/pch.h"
#include "Serum/UI/Types/Color.h"

namespace Serum::UI {
    class Converter {
    public:
        static ImVec4 ToImVec4(const Color& color);

        static Color ToColor(const ImVec4& color);

        static ImVec2 ToImVec2(const glm::vec2& pos);

        static glm::vec2 ToVec2(const ImVec2& pos);
    };
}