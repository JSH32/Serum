#pragma once

#include "SFML/Window/Event.hpp"

namespace Serum2D::Editor {
    class EditorPanel {
    public:
        virtual void OnEvent(sf::Event event) = 0;
        virtual void OnUpdate() = 0;

        [[nodiscard]] bool ReceiveEvents() const { return receiveEvents; }
    protected:
        void ShouldReceiveEvents(bool receive) { this->receiveEvents = receive; }
    private:
        bool receiveEvents = false;
    };
}