#include "serum2d/core/components/transform2d.hpp"
#include "raymath.h"

namespace Serum2D::Core::Components {
Transform2D::Transform2D(Vector2 translation, const Vector2 scale,
                         float rotation) {
  this->setRotation(rotation);
  this->setScale(scale);
  this->setTranslation(translation);
}

void Transform2D::setScale(Vector2 scale) {
  this->transform.scale = Vector3{.x = scale.x, .y = scale.y, .z = 0};
}

void Transform2D::setTranslation(Vector2 translation) {
  this->transform.translation =
      Vector3{.x = translation.x, .y = translation.y, .z = 0};
}

void Transform2D::setRotation(float rotation) {
  this->transform.rotation = QuaternionFromMatrix(MatrixRotateZ(rotation));
}

Vector2 Transform2D::getTranslation() {
  return Vector2{.x = this->transform.rotation.x,
                 .y = this->transform.rotation.y};
}

Vector2 Transform2D::getScale() {
  return Vector2{.x = this->transform.scale.x, .y = this->transform.scale.y};
}

float Transform2D::getRotation() {
  Vector3 outAxis;
  float outAngle;

  QuaternionToAxisAngle(this->transform.rotation, &outAxis, &outAngle);
  return outAngle;
}
} // namespace Serum2D::Core::Components