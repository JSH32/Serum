#pragma once

#include <entt/entt.hpp>
#include <raylib.h>
#include <string>

namespace Serum2D::Core {
class Entity;

class Scene {
public:
  explicit Scene(const std::string_view &name) : name(name) {}

  const std::vector<Entity> &getEntities() { return entities; }

  Entity createEntity(const std::string &entityName = std::string());
  void destroyEntity(Entity entity);

  void update();
  void render(RenderTexture &target);

  std::string name;
  entt::registry registry;

private:
  std::vector<Entity> entities;
};
} // namespace Serum2D::Core