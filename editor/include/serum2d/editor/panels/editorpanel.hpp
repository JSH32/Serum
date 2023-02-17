#pragma once

namespace Serum2D::Editor {
class EditorPanel {
public:
  virtual ~EditorPanel() = default;
  virtual void onUpdate() {}
};
} // namespace Serum2D::Editor