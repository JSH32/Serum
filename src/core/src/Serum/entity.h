#pragma once

#include <utility>
#include "entt.hpp"
#include "scene.h"

namespace Serum2D::Core {
    class Entity {
    public:
        Entity() = default;
        Entity(entt::entity handle, Scene* scene);

        template<typename T, typename... Args>
        T& addComponent(Args&&... args) {
            T& component = scene->registry.emplace<T>(entityHandle, std::forward<Args>(args)...);
            return component;
        }

        template<typename T>
        T& getComponent() {
            return scene->registry.get<T>(entityHandle);
        }

        template<typename T>
        [[nodiscard]] bool hasComponent() const {
            return scene->registry.all_of<T>(entityHandle);
        }

        template<typename T>
        void removeComponent() const {
            scene->registry.remove<T>(entityHandle);
        }

        operator bool() const { return entityHandle != entt::null; }
        operator uint32_t() const { return (uint32_t)entityHandle; }
    	operator entt::entity() const { return entityHandle; }

        bool operator==(const Entity& other) const {
            return entityHandle == other.entityHandle && scene == other.scene;
        }

        bool operator!=(const Entity& other) const {
            return !(*this == other);
        }
    private:
        entt::entity entityHandle{ entt::null };
        Scene* scene = nullptr;
    };
}