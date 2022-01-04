#pragma once

#include <string>
#include <utility>

namespace Serum2D::Core::Components {
    class TagComponent {
    public:
        explicit TagComponent(std::string tag) : tag(std::move(tag)) {}
        TagComponent() = default;
        TagComponent(const TagComponent&) = default;

        std::string tag;
    };
}