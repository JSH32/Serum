#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/String.hpp>
#include "editor.h"
#include "log.h"

int main() {
    sf::RenderWindow window(
            sf::VideoMode(1280, 720),
            sf::String("Serum"));
    window.setFramerateLimit(60);

    Serum2D::Log::Init();
    S2D_CORE_INFO("Opening Serum2D editor");

    Serum2D::Editor::Editor editor(window);
    editor.run();

    return 0;
}