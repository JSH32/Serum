#pragma once

#include "Serum/pch.h"

namespace Serum {
    class UIManager {
    public:
        UIManager(GLFWwindow *window, const std::string &glslVer);
        ~UIManager();

        void EnableDocking(bool enable);

        bool IsDockingEnabled() const;

        void Render();
    private:
        static void SetTheme();

        bool docking;
    };
}