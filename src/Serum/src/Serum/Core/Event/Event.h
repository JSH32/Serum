#pragma once

#include <functional>

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
                                EventType GetEventType() override { return GetStaticType(); }\
                                const char* GetName() override { return #type; }



#define EVENT_CLASS_CATEGORY(category) int GetCategoryFlags() override { return category; }

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

    class Event {
    public:
        virtual ~Event() = default;

        virtual EventType GetEventType() = 0;
        virtual const char* GetName() = 0;
        virtual int GetCategoryFlags() = 0;
        virtual std::string ToString() { return GetName(); }

        bool IsInCategory(EventCategory category) {
            return GetCategoryFlags() & category;
        }
    };

    using EventCallbackFn = std::function<void(Event&)>;

    class EventDispatcher {
    public:
        explicit EventDispatcher(Event& event) : event(event) {}

        template<typename T, typename F>
        bool Dispatch(const F& func) {
            if (event.GetEventType() == T::GetStaticType()) {
                func(static_cast<T&>(event));
                return true;
            }
            return false;
        }
    private:
        Event& event;
    };

    inline std::ostream& operator<<(std::ostream& os, Event& e) {
        return os << e.ToString();
    }
}
