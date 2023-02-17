#include "serum2d/core/window.hpp"
#include "raylib.h"
#include "serum2d/core/log.hpp"

namespace Serum2D::Core {
Window::Window(const int screenWidth, const int screenHeight,
               const std::string_view title) {

  SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
  InitWindow(screenWidth, screenHeight, title.data());
  SetTargetFPS(120);

  Serum2D::Log::init();
  S2D_CORE_INFO("Initializing Serum2D window.");
};

Window::~Window() { CloseWindow(); }
} // namespace Serum2D::Core