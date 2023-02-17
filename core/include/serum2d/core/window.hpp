#include <string_view>

namespace Serum2D::Core {
/**
 * @brief Simple window initialization wrapper around Raylib.
 * This window will live until its destroyed.
 * Only one window may exist at a time.
 */
class Window {
public:
  explicit Window(const int screenWidth, const int screenHeight,
                  const std::string_view title);

  ~Window();
};
} // namespace Serum2D::Core