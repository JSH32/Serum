#include "serum2d/core/entity.hpp"

namespace Serum2D::Core {
Entity::Entity(const entt::entity handle, Scene *scene)
    : entityHandle(handle), scene(scene) {}
} // namespace Serum2D::Core