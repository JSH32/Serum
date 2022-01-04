#include "scene.h"
#include "entity.h"
#include "components/tag.h"
#include "SFML/Graphics/Transformable.hpp"

namespace Serum2D::Core {
    void Scene::destroyEntity(Entity entity) {
        registry.destroy(entity);
    }

    Entity Scene::createEntity(const std::string& entityName) {
        Entity entity = { registry.create(), this };
        entity.addComponent<Components::TagComponent>(entityName.empty() ? "New entity" : entityName);
        entity.addComponent<sf::Transformable>();
        return entity;
    }
}