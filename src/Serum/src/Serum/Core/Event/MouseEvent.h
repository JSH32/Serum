#pragma once

#include "Serum/pch.h"

#include "Event.h"
#include "Serum/Core/Input/MouseCodes.h"

namespace Serum {
    struct MouseMovedEvent : public Event {
        MouseMovedEvent(const float x, const float y)
                : m_MouseX(x), m_MouseY(y) {}

        float GetX() { return m_MouseX; }
        float GetY() { return m_MouseY; }

        std::string ToString() override {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    private:
        float m_MouseX, m_MouseY;
    };

    struct MouseScrolledEvent : public Event {
        MouseScrolledEvent(float xOffset, float yOffset) : xOffset(xOffset), yOffset(yOffset) {}

        float GetXOffset() const { return xOffset; }
        float GetYOffset() const { return yOffset; }

        std::string ToString() override {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    private:
        float yOffset, xOffset;
    };

    class MouseButtonEvent : public Event {
    public:
        MouseCode GetMouseButton() const { return button; }

        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)
    protected:
        explicit MouseButtonEvent(MouseCode button) : button(button) {}

        MouseCode button;
    };

    struct MouseButtonPressedEvent : public MouseButtonEvent {
        explicit MouseButtonPressedEvent(MouseCode button) : MouseButtonEvent(button) {}

        std::string ToString() override {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    struct MouseButtonReleasedEvent : public MouseButtonEvent {
        explicit MouseButtonReleasedEvent(const MouseCode button) : MouseButtonEvent(button) {}

        std::string ToString() override {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };
}