#include <raylib.h>

namespace Serum2D::Core::Components {
class Transform2D;

/**
 * @brief Class implemented by any renderable object that can be drawn.
 * An entity should only have one of these at a time.
 */
class Drawable {
public:
  /**
   * @brief Draw the entity on the provided {@link RenderTexture}
   * @param target texture to render to
   */
  virtual void draw(Transform2D &transform) const = 0;
};
} // namespace Serum2D::Core::Components