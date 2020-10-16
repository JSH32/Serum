#pragma once

#include "Serum/UI/Internal/Drawable.h"
#include "Serum/UI/Plugin/Pluginable.h"

namespace Serum::UI {
    class WidgetContainer;

    class Widget : public Drawable, Pluginable {
    public:
        Widget();

        virtual void Draw() override;

        void LinkTo(const Widget& widget);

        void Destroy();

        bool IsDestroyed() const;

        bool HasParent() const;

        void SetParent(WidgetContainer* newParent);

        WidgetContainer* GetParent();

        bool enabled = true;
        bool lineBreak = true;
    protected:
        virtual void Draw_Impl() = 0;

        WidgetContainer* parent;
        std::string widgetID = "?";
        bool autoExecutePlugins = true;
    private:
        static uint WIDGET_ID_INCREMENT;
        bool destroyed = false;
    };
}