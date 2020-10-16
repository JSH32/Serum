#pragma once

#include "Plugin.h"

namespace Serum::UI {
    class Pluginable {
    public:
        ~Pluginable() {
            RemoveAllPlugins();
        }

        void ExecutePlugins() {
            for (auto& plugin : plugins)
                plugin->Execute();
        };

        void RemoveAllPlugins() {
            for (auto& plugin : plugins)
                delete plugin;

            plugins.clear();
        }

        template<typename T>
        T* GetPlugin() {
            static_assert(std::is_base_of<Plugin, T>::value, "T should derive from Plugin");

            for (auto & plugin : plugins) {
                T* result = dynamic_cast<T*>(plugin);
                if (result)
                    return result;
            }

            return nullptr;
        }

        template<typename T, typename... Args>
        T& AddPlugin(Args&& ... p_args) {
            static_assert(std::is_base_of<Plugin, T>::value, "T should derive from Plugin");

            T* newPlugin = new T(std::forward<Args>(p_args)...);
            plugins.push_back(newPlugin);
            return *newPlugin;
        }
    private:
        std::vector<Plugin*> plugins;
    };
}