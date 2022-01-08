#include "scene.h"
#include "entity.h"
#include "Serum/components/entity_info.h"
#include "SFML/Graphics/Transformable.hpp"
#include "Serum/components/shape.h"

namespace Serum2D::Core {
    void Scene::destroyEntity(Entity entity) {
        registry.destroy(entity);
    }

    Entity Scene::createEntity(const std::string& entityName) {
        Entity entity = { registry.create(), this };
        entity.addComponent<Components::EntityInfoComponent>(entityName.empty() ? "New entity" : entityName);
        entity.addComponent<sf::Transformable>();
        return entity;
    }

    void Scene::render(sf::RenderTarget &target) {
        registry.each([&](auto entityID) {
            Entity entity = { entityID, this };

            if (!entity.hasComponent<Core::Components::EntityInfoComponent>()) {
                S2D_ERROR("An Entity did not have a EntityInfo component, this should not happen. It has been added automatically.");
                entity.addComponent<Core::Components::EntityInfoComponent>();
            }

            auto& eInfo = entity.getComponent<Core::Components::EntityInfoComponent>();
            if (!eInfo.enabled) return;

            // Add a transform component back
            if (!entity.hasComponent<sf::Transformable>()) {
                S2D_ERROR("Entity \"{0}\" did not have a Transform component, this should not happen. It has been added automatically.", eInfo.tag);
                entity.template addComponent<sf::Transformable>();
            }

            auto& transform = entity.getComponent<sf::Transformable>();

            if (entity.hasComponent<Components::ShapeComponent>())
                target.draw(entity.getComponent<Components::ShapeComponent>(), sf::RenderStates(transform.getTransform()));
        });
    }
}