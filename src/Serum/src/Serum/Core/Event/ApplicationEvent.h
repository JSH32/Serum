#pragma once

#include "Event.h"

#include "Serum/pch.h"

namespace Serum {
    struct WindowResizeEvent : public Event {
        WindowResizeEvent(unsigned int width, unsigned int height) : Width(width), Height(height) {}

        unsigned int GetWidth() const { return Width; }
        unsigned int GetHeight() const { return Height; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << Width << ", " << Height;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    private:
        unsigned int Width, Height;
    };

    struct WindowCloseEvent : public Event {
        WindowCloseEvent() = default;

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    struct AppTickEvent : public Event {
        AppTickEvent() = default;

        EVENT_CLASS_TYPE(AppTick)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    struct AppUpdateEvent : public Event {
        AppUpdateEvent() = default;

        EVENT_CLASS_TYPE(AppUpdate)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    struct AppRenderEvent : public Event {
        AppRenderEvent() = default;

        EVENT_CLASS_TYPE(AppRender)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };
}