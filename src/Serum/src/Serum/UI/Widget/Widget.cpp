#include "Widget.h"

namespace Serum::UI {
    uint Widget::WIDGET_ID_INCREMENT = 0;

    Widget::Widget() {
        widgetID = "##" + std::to_string(WIDGET_ID_INCREMENT++);
    }

    void Widget::LinkTo(const Widget& widget) {
        widgetID = widget.widgetID;
    }

    void Widget::Destroy() {
        destroyed = true;
    }

    void Widget::SetParent(WidgetContainer* newParent) {
        this->parent = newParent;
    }

    bool Widget::IsDestroyed() const {
        return destroyed;
    }

    bool Widget::HasParent() const {
        return parent;
    }

    WidgetContainer* Widget::GetParent() {
        return parent;
    }

    void Widget::Draw() {
        if (enabled) {
            Draw_Impl();

            if (autoExecutePlugins)
                ExecutePlugins();

            if (!lineBreak)
                ImGui::SameLine();
        }
    }
}