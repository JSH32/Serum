#pragma once

#include <functional>

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
                                EventType GetEventType() const override { return GetStaticType(); }\
                                const char* GetName() const override { return #type; }



#define EVENT_CLASS_CATEGORY(category) int GetCategoryFlags() const override { return category; }

namespace Serum {
    enum class EventType {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum EventCategory {
        None = 0,
        EventCategoryApplication,
        EventCategoryInput,
        EventCategoryKeyboard,
        EventCategoryMouse,
        EventCategoryMouseButton
    };

    struct Event {
        virtual ~Event() = default;

        bool Handled = false;

        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }

        bool IsInCategory(EventCategory category) {
            return GetCategoryFlags() & category;
        }
    };

    using EventCallbackFn = std::function<void(Event&)>;

    class EventDispatcher {
    public:
        EventDispatcher(Event& event) : event(event) {}

        template<typename T, typename F>
        bool Dispatch(const F& func) {
            if (event.GetEventType() == T::GetStaticType()) {
                event.Handled = func(static_cast<T&>(event));
                return true;
            }
            return false;
        }
    private:
        Event& event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e) {
        return os << e.ToString();
    }
}
