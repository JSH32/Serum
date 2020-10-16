#pragma once

#include "Serum/UI/Internal/Drawable.h"
#include "Serum/UI/Internal/WidgetContainer.h"

namespace Serum::UI {
    class Panel : public Drawable, public WidgetContainer {
    public:
        Panel();

        void Draw() override;

        const std::string& GetPanelID() const;

        bool enabled = true;
    protected:
        virtual void Draw_Impl() = 0;
        std::string panelID;
    private:
        static uint PANEL_ID_INCREMENT;
    };
}