#include "Panel.h"

namespace Serum::UI {
    Panel::Panel() {
        this->panelID = "##" + std::to_string(PANEL_ID_INCREMENT++);
    }
    void Panel::Draw() {
        if (enabled)
            Draw_Impl();
    }
    const std::string & Panel::GetPanelID() const {
        return panelID;
    }
}