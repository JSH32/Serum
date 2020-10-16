#include "WidgetContainer.h"

namespace Serum::UI {
    void WidgetContainer::RemoveWidget(Widget &widget) {
        auto found = std::find_if(widgets.begin(), widgets.end(), [&widget](std::pair<Widget*, MemoryMode>& pair) {
            return pair.first == &widget;
        });

        if (found != widgets.end()) {
            if (found->second == MemoryMode::INTERNAL_MANAGMENT)
                delete found->first;

            widgets.erase(found);
        }
    }

    void WidgetContainer::RemoveAll() {
        std::for_each(widgets.begin(), widgets.end(), [](std::pair<Widget*, MemoryMode>& pair) {
            if (pair.second == MemoryMode::INTERNAL_MANAGMENT)
                delete pair.first;
        });

        widgets.clear();
    }

    void WidgetContainer::LinkWidget(Widget &widget, bool manage) {
        widgets.emplace_back(&widget, manage ? MemoryMode::INTERNAL_MANAGMENT : MemoryMode::EXTERNAL_MANAGMENT);
        widget.SetParent(this);
    }

    void WidgetContainer::UnlinkWidget(Widget& widget) {
        auto found = std::find_if(widgets.begin(), widgets.end(), [&widget](std::pair<Widget*, MemoryMode>& pair){
            return pair.first == &widget;
        });

        if (found != widgets.end()) {
            widget.SetParent(nullptr);
            widgets.erase(found);
        }
    }

    void WidgetContainer::InvokeGC() {
        widgets.erase(std::remove_if(widgets.begin(), widgets.end(), [](std::pair<Widget*, MemoryMode>& pair) {
            bool destroy = pair.first && pair.first->IsDestroyed();

            if (destroy && pair.second == MemoryMode::INTERNAL_MANAGMENT)
                delete pair.first;

            return destroy;
        }), widgets.end());
    }

    void WidgetContainer::DrawWidgets() {
        InvokeGC();

        for (auto& widget : widgets)
            widget.first->Draw();
    }

    std::vector<std::pair<Widget *, MemoryMode>> & WidgetContainer::GetWidgets() {
        return widgets;
    }
}