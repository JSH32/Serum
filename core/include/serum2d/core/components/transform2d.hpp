#pragma once

#include "raylib.h"
#include <string>
#include <utility>

namespace Serum2D::Core::Components {
/**
 * @brief Wrapper around raylib's {@link Transform}.
 */
class Transform2D {
public:
  Transform2D(Vector2 translation = {0, 0}, const Vector2 scale = {1, 1},
              float rotation = 0.f);

  void setTranslation(Vector2 translation);
  void setScale(Vector2 scale);
  void setRotation(float rotation);

  Vector2 getTranslation();
  Vector2 getScale();
  float getRotation();

  /**
   * @brief Dont directly access this.
   */
  Transform transform;
};
} // namespace Serum2D::Core::Components