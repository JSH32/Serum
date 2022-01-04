#include <iostream>
#include "scene.h"
#include "entity.h"
#include "components/tag.h"
#include "SFML/Graphics/Transformable.hpp"
#include "components/shape.h"

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

    void Scene::Render(sf::RenderTarget &target) {
        registry.each([&](auto entityID) {
            Entity entity = { entityID, this };

            if (!entity.hasComponent<sf::Transformable>()) {
                // TODO: Assert/log an error here. All components should have a transform

                return;
            }

            auto& transform = entity.getComponent<sf::Transformable>();

            if (entity.hasComponent<Components::ShapeComponent>())
                target.draw(entity.getComponent<Components::ShapeComponent>(), sf::RenderStates(transform.getTransform()));
        });
    }
}