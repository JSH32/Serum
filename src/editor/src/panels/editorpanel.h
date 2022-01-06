#pragma once

#include "SFML/Window/Event.hpp"

namespace Serum2D::Editor {
    class EditorPanel {
    public:
        virtual void onEvent(sf::Event event) {};
        virtual void onUpdate() = 0;

        [[nodiscard]] bool shouldReceiveEvents() const { return receiveEvents; }
    protected:
        void setReceiveEvents(bool receive) { this->receiveEvents = receive; }
    private:
        bool receiveEvents = false;
    };
}