#include "raylib.h"
#include "serum2d/editor/panels/editorpanel.hpp"
#include <chrono>
#include <serum2d/core/serum2d.hpp>
#include <vector>

namespace Serum2D::Editor {
/**
 * @brief Only one editor instance should exist at a time.
 */
class Editor {
public:
  explicit Editor();
  ~Editor();

  void run();
  void update() const;

private:
  static void startDockSpace();

  std::vector<std::unique_ptr<EditorPanel>> panels;
  RenderTexture texture;
  Core::Window window;

  Core::Scene scene;
  Core::Entity selectedEntity;
};
} // namespace Serum2D::Editor