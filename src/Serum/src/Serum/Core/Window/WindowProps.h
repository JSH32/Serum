#pragma once

#include "Serum/pch.h"
#include "WindowData.h"

namespace Serum {
    struct WindowProps {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProps(const std::string& title = "Serum Window",
                    unsigned int width = 1280,
                    unsigned int height = 720)
                    : Title(title), Width(width), Height(height) {}
    };
}