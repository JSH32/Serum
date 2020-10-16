#pragma once

namespace Serum::UI {
    class Drawable {
    public:
        virtual void Draw() = 0;
    protected:
        virtual ~Drawable() = default;
    };
}