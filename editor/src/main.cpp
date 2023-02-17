#include "serum2d/editor/editor.hpp"

int main(int argc, char **argv) {
  auto editor = Serum2D::Editor::Editor();
  editor.run();

  return 0;
}

// int main() {
//     sf::RenderWindow window(
//             sf::VideoMode(1280, 720),
//             sf::String("Serum"));
//     window.setFramerateLimit(60);

// Serum2D::Log::init();
// S2D_CORE_INFO("Opening Serum2D editor");

//     Serum2D::Editor::Editor editor(window);
//     editor.run();

//     return 0;
// }