#pragma once

#include <string>
#include "entt.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

namespace Serum2D::Core {
    class Entity;

    class Scene {
    public:
        explicit Scene(const std::string_view& name) : name(name) {}

        const std::vector<Entity>& getRootOrderedEntities() { return rootOrderedEntities; }

        Entity createEntity(const std::string& entityName = std::string());
        void destroyEntity(Entity entity);

        void render(sf::RenderTarget& target);

        std::string name;
        entt::registry registry;
    private:
        std::vector<Entity> rootOrderedEntities;
    };
}