#include "Color.h"

namespace Serum::UI {
    const Color Color::Red     = {1.f, 0.f, 0.f};
    const Color Color::Green   = {0.f, 1.f, 0.f};
    const Color Color::Blue    = {0.f, 0.f, 1.f};
    const Color Color::White   = {1.f, 1.f, 1.f};
    const Color Color::Black   = {0.f, 0.f, 0.f};
    const Color Color::Grey    = {0.5f, 0.5f, 0.5f};
    const Color Color::Yellow  = {1.f, 1.f, 0.f};
    const Color Color::Cyan    = {0.f, 1.f, 1.f};
    const Color Color::Magenta = {1.f, 0.f, 1.f};

    bool Color::operator==(const Color &color) const {
        return this->r == color.r && this->g == color.g && this->b == color.b && this->a == color.a;
    }

    bool Color::operator!=(const Color &color) const {
        return !operator==(color);
    }
}