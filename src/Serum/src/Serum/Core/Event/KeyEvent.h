#pragma once

#include "Serum/pch.h"

#include "Event.h"
#include "Serum/Core/Input/KeyCodes.h"

namespace Serum {
    class KeyEvent : public Event {
    public:
        KeyCode GetKeyCode() const { return keycode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
    protected:
        explicit KeyEvent(const KeyCode keycode) : keycode(keycode) {}

        KeyCode keycode;
    };

    struct KeyPressedEvent : public KeyEvent {
        KeyPressedEvent(const KeyCode keycode, const uint16_t repeatCount) : KeyEvent(keycode), repeat_count(repeatCount) {}

        uint GetRepeatCount() const { return repeat_count; }

        std::string ToString() override {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << keycode << " (" << repeat_count << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)
    private:
        uint repeat_count;
    };

    struct KeyReleasedEvent : public KeyEvent {
        explicit KeyReleasedEvent(const KeyCode keycode) : KeyEvent(keycode) {}

        std::string ToString() override {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << keycode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };

    struct KeyTypedEvent : public KeyEvent {
        explicit KeyTypedEvent(const KeyCode keycode) : KeyEvent(keycode) {}

        std::string ToString() override {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << keycode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyTyped)
    };
}