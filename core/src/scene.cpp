#include "serum2d/core/scene.hpp"
#include "serum2d/core/entity.hpp"
#include "serum2d/core/log.hpp"

#include "serum2d/core/components/entity_info.hpp"
#include "serum2d/core/components/transform2d.hpp"

namespace Serum2D::Core {
void Scene::destroyEntity(const Entity entity) {
  entities.erase(std::remove(entities.begin(), entities.end(), entity),
                 entities.end());
  registry.destroy(entity);
}

Entity Scene::createEntity(const std::string &entityName) {
  Entity entity = {registry.create(), this};
  entity.addComponent<Components::EntityInfoComponent>(
      entityName.empty() ? "New entity" : entityName);
  entity.addComponent<Components::Transform2D>();

  entities.push_back(entity);

  return entity;
}

void Scene::render(RenderTexture &target) {
  for (auto it = entities.rbegin(); it != entities.rend(); ++it) {
    auto &entity = *it;

    // const auto &transform = entity.getComponent<Components::Transform2D>();
  }
}

void Scene::update() {
  for (auto it = entities.rbegin(); it != entities.rend(); ++it) {
    auto &entity = *it;

    if (!entity.hasComponent<Components::EntityInfoComponent>()) {
      S2D_WARN("An Entity did not have a EntityInfo component, this should "
               "not happen. It has been added automatically.");
      entity.addComponent<Components::EntityInfoComponent>();
    }

    auto &eInfo = entity.getComponent<Components::EntityInfoComponent>();
    if (!eInfo.enabled)
      return;

    // Add a transform component back
    if (!entity.hasComponent<Components::Transform2D>()) {
      S2D_WARN("Entity \"{0}\" did not have a Transform component, this "
               "should not happen. It has been added automatically.",
               eInfo.tag);
      entity.addComponent<Components::Transform2D>();
    }
  }
}
} // namespace Serum2D::Core