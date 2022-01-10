#pragma once

#include "SFML/Window/Event.hpp"

namespace Serum2D::Editor {
    class EditorPanel {
    public:
	    virtual ~EditorPanel() = default;
	    virtual void onEvent(sf::Event event) {}
        virtual void onUpdate() {}

        [[nodiscard]] bool shouldReceiveEvents() const { return receiveEvents; }
    protected:
        void setReceiveEvents(const bool receive) { this->receiveEvents = receive; }
    private:
        bool receiveEvents = false;
    };
}
