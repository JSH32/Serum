#include "entity.h"

namespace Serum2D::Core {
    Entity::Entity(const entt::entity handle, Scene *scene)
        : entityHandle(handle), scene(scene) {}
}