#include "serum2d/core/components/shape.hpp"
#include "rlgl.h"

namespace Serum2D::Core::Components {
ShapeComponent::ShapeComponent(const ShapeType shapeType)
    : shapeType(shapeType) {}

void ShapeComponent::setShape(ShapeType newShapeType) {}

void ShapeComponent::draw(Transform2D &transform) const {
  auto translation = transform.getTranslation();
  auto scale = transform.getScale();

  rlPushMatrix();

  rlTranslatef(translation.x, translation.y, 1);
  rlRotatef(transform.getRotation(), 0, 0, 0);
  rlScalef(scale.x, scale.y, 1);

  if (this->shapeType == ShapeType::Rectangle) {
    DrawRectangle(0, 0, size.x, size.y, this->color);
  } else if (this->shapeType == ShapeType::Circle) {
    DrawEllipse(0, 0, size.x, size.y, this->color);
  }

  rlPopMatrix();
}
} // namespace Serum2D::Core::Components