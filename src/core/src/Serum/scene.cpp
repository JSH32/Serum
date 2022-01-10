#include <SFML/Graphics/Transformable.hpp>
#include <entt.hpp>

#include "Serum/components/entityinfo.h"
#include "Serum/components/shape.h"

#include "scene.h"
#include "entity.h"
#include "log.h"

namespace Serum2D::Core {
    void Scene::destroyEntity(const Entity entity) {
        rootOrderedEntities.erase(std::remove(rootOrderedEntities.begin(), rootOrderedEntities.end(), entity),
                              rootOrderedEntities.end());
        registry.destroy(entity);
    }

    Entity Scene::createEntity(const std::string& entityName) {
        Entity entity = { registry.create(), this };
        entity.addComponent<Components::EntityInfoComponent>(entityName.empty() ? "New entity" : entityName);
        entity.addComponent<sf::Transformable>();

        rootOrderedEntities.push_back(entity);

        return entity;
    }

    void Scene::render(sf::RenderTarget &target) {
    	for (auto it =  rootOrderedEntities.rbegin(); it != rootOrderedEntities.rend(); ++it) {
            auto& entity = *it;

            if (!entity.hasComponent<Components::EntityInfoComponent>()) {
                S2D_ERROR("An Entity did not have a EntityInfo component, this should not happen. It has been added automatically.");
                entity.addComponent<Components::EntityInfoComponent>();
            }

            auto& eInfo = entity.getComponent<Components::EntityInfoComponent>();
            if (!eInfo.enabled) return;

            // Add a transform component back
            if (!entity.hasComponent<sf::Transformable>()) {
                S2D_ERROR("Entity \"{0}\" did not have a Transform component, this should not happen. It has been added automatically.", eInfo.tag);
                entity.addComponent<sf::Transformable>();
            }

            const auto& transform = entity.getComponent<sf::Transformable>();

            if (entity.hasComponent<Components::ShapeComponent>())
                target.draw(entity.getComponent<Components::ShapeComponent>(), sf::RenderStates(transform.getTransform()));
    	}
    }
}
