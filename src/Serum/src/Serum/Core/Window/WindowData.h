#pragma once

#include "Serum/pch.h"

#include "Serum/Core/Event/Event.h"

struct WindowData {
    std::string Title;
    unsigned int Width, Height;
    bool VSync;

    Serum::EventCallbackFn EventCallback;
};