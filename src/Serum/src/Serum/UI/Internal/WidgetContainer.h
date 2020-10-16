#pragma once

#include "Serum/pch.h"

#include "Serum/UI/Internal/MemoryMode.h"
#include "Serum/UI/Widget/Widget.h"

namespace Serum::UI {
    class WidgetContainer {
        void RemoveWidget(Widget& p_widget);

        void RemoveAll();

        void LinkWidget(Widget& widget, bool manage = true);

        void UnlinkWidget(Widget& widget);

        void InvokeGC();

        void DrawWidgets();

        template <typename T, typename ... Args>
        T& CreateWidget(Args&&... args) {
            widgets.emplace_back(new T(args...), MemoryMode::INTERNAL_MANAGMENT);
            T& instance = *reinterpret_cast<T*>(widgets.back().first);
            instance.SetParent(this);
            return instance;
        }

        std::vector<std::pair<Widget*, MemoryMode>>& GetWidgets();

    protected:
        std::vector<std::pair<Widget*, MemoryMode>> widgets;
    };
}