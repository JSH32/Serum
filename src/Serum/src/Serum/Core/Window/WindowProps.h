#pragma once

#include "Serum/pch.h"
#include "WindowData.h"

namespace Serum {
    struct WindowProps {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        explicit WindowProps(std::string title,
                    unsigned int width = 1280,
                    unsigned int height = 720)
                    : Title(std::move(title)), Width(width), Height(height) {}
    };
}