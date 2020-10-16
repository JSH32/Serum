#pragma once

namespace Serum::UI {
    class Color {
    public:
        Color(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f)
                : r(r), g(g), b(b), a(a) {};

        float r;
        float g;
        float b;
        float a;

        static const Color Red;
        static const Color Green;
        static const Color Blue;
        static const Color White;
        static const Color Black;
        static const Color Grey;
        static const Color Yellow;
        static const Color Cyan;
        static const Color Magenta;

        bool operator==(const Color& color) const;

        bool operator!=(const Color& color) const;
    };
}