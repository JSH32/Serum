#include "drawable.hpp"
#include "transform2d.hpp"

namespace Serum2D::Core::Components {
enum class ShapeType { Circle, Rectangle };

class ShapeComponent final : public Drawable {
public:
  explicit ShapeComponent(ShapeType shapeType);

  /**
   * Recreate the internal shape with a new type, this will attempt to transfer
   * over shape properties
   */
  void setShape(ShapeType newShapeType);

  ShapeType shapeType;
  Color color;

  Vector2 size = {1, 1};

  void draw(Transform2D &transform) const override;
};
} // namespace Serum2D::Core::Components