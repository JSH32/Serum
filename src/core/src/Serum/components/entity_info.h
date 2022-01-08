#pragma once

#include <string>
#include <utility>

namespace Serum2D::Core::Components {
    class EntityInfoComponent {
    public:
        explicit EntityInfoComponent(std::string tag, bool enabled = true)
            : tag(std::move(tag)), enabled(enabled) {}
        EntityInfoComponent() = default;
        EntityInfoComponent(const EntityInfoComponent&) = default;

        std::string tag;
        bool enabled{};
    };
}