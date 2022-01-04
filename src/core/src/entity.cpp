#include "entity.h"

namespace Serum2D::Core {
    Entity::Entity(entt::entity handle, Scene *scene)
        : entityHandle(handle), scene(scene) {}
}