#pragma once

#include <string_view>
#include <string>
#include <vector>
#include "entt.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

namespace Serum2D::Core {
    class Entity;

    class Scene {
    public:
        explicit Scene(const std::string_view& name) : name(name) {};

        Entity createEntity(const std::string& entityName = std::string());
        void destroyEntity(Entity entity);

        void render(sf::RenderTarget& target);

        std::string name;
        entt::registry registry;
    };
}