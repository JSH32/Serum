#pragma once

namespace Serum::UI {
    class Plugin {
    public:
        virtual void Execute() = 0;

        // Store whatever data you like here
        void* userData = nullptr;
    };
}