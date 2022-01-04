#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Window/Event.hpp>
#include <imgui-SFML.h>
#include "imgui.h"
#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "grid.h"
#include "editor.h"

///**
// * After this function the dockspace is still open so a MenuBar can be rendered.
// * Please close this dockspace with ImGui::End after
// */
//
//
//int main() {
//    sf::RenderWindow window(
//            sf::VideoMode(1280, 720),
//            sf::String("Serum"));
//    window.setFramerateLimit(60);
//
//    (void)ImGui::SFML::Init(window);
//
//    ImGuiIO& io = ImGui::GetIO(); (void)io;
//    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
//    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
//    io.ConfigWindowsMoveFromTitleBarOnly = true;
//
//    sf::Clock deltaTime;
//
//    sf::RenderTexture renderTexture;
//    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
//    renderTexture.setView(view);
//
//    sf::CircleShape shape(50);
//    shape.setPosition(sf::Vector2f(0.f, 0.f));
//    shape.setFillColor(sf::Color(100, 250, 50));
//
//    bool moving = false;
//    sf::Vector2f oldPos;
//
//    bool focusSceneView = false;
//    float zoom = 1;
//
//    sf::RectangleShape gridLineY, gridLineX;
//    gridLineY.setFillColor(sf::Color::Green);
//    gridLineX.setFillColor(sf::Color::Red);
//
//    while (window.isOpen()) {
//        sf::Event event{};
//        while (window.pollEvent(event)) {
//            ImGui::SFML::ProcessEvent(window, event);
//
//            if (event.type == sf::Event::Closed)
//                window.close();
//
//            if (focusSceneView) {
//                if (event.type == sf::Event::MouseButtonPressed) {
//                    if (event.mouseButton.button == 1) {
//                        moving = true;
//                        oldPos = renderTexture.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, -event.mouseButton.y));
//                    }
//                } else if (event.type == sf::Event::MouseButtonReleased) {
//                    if (event.mouseButton.button == 1)
//                        moving = false;
//                } else if (event.type == sf::Event::MouseMoved) {
//                    if (moving) {
//                        const sf::Vector2f newPos = renderTexture.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, -event.mouseMove.y));
//                        const sf::Vector2f deltaPos = oldPos - newPos;
//
//                        view.setCenter(view.getCenter() + deltaPos);
//                        renderTexture.setView(view);
//                        //grid.setPosition(view.getCenter());
//                        //grid.setOrigin(view.getCenter());
//                        //grid.setPosition(view.getViewport().getPosition());
//                        oldPos = renderTexture.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, -event.mouseMove.y));
//                    }
//                } else if (event.type == sf::Event::MouseWheelScrolled) {
//                    if (!moving) {
//                        if (event.mouseWheelScroll.delta <= -1)
//                            zoom = std::min(2.f, zoom + .1f);
//                        else if (event.mouseWheelScroll.delta >= 1)
//                            zoom = std::max(.5f, zoom - .1f);
//
//                        view.setSize(renderTexture.getDefaultView().getSize());
//                        view.zoom(zoom);
//                        renderTexture.setView(view);
//                    }
//                }
//            }
//        }
//
//        ImGui::SFML::Update(window, deltaTime.restart());
//
//        imGuiDockspace();
//        if (ImGui::BeginMenuBar()) {
//                if (ImGui::BeginMenu("File")) {
//                    ImGui::MenuItem("Exit");
//                    ImGui::EndMenu();
//                }
//                ImGui::EndMenuBar();
//        }
//        ImGui::End(); // Close dockspace
//
//        ImGui::Begin("Hello, world!");
//        ImGui::Button("Look at this pretty button");
//        ImGui::End();
//
//        renderTexture.clear(sf::Color(50, 50, 50));
//        auto relativeViewCoords = renderTexture.mapPixelToCoords(sf::Vector2i(0.f, 0.f), view);
//        gridLineY.setPosition(sf::Vector2f(relativeViewCoords.x, 0));
//        gridLineY.setSize(sf::Vector2f(view.getSize().x, 2));
//        renderTexture.draw(gridLineY);
//
//        gridLineX.setPosition(sf::Vector2f(0, relativeViewCoords.y));
//        gridLineX.setSize(sf::Vector2f(2, view.getSize().y));
//        renderTexture.draw(gridLineX);
//
//        renderTexture.draw(shape);
//
//        {
//            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
//            ImGui::Begin("Scene view");
//
//            float windowWidth = ImGui::GetContentRegionAvail().x;
//            float windowHeight = ImGui::GetContentRegionAvail().y;
//            if ((uint)windowWidth != renderTexture.getSize().x || (uint)windowHeight != renderTexture.getSize().y) {
//                renderTexture.create((uint)windowWidth, (uint)windowHeight);
//                view.setSize(windowWidth, windowHeight);
//                renderTexture.setView(view);
//            }
//
//            ImGui::Image(sf::Sprite(renderTexture.getTexture()));
//            focusSceneView = ImGui::IsWindowFocused();
//           // ImGui::
//            ImGui::End();
//
//            ImGui::PopStyleVar();
//        }
//
//        window.clear();
//        ImGui::SFML::Render(window);
//        window.display();
//    }
//
//    return 0;
//}

int main() {
    sf::RenderWindow window(
            sf::VideoMode(1280, 720),
            sf::String("Serum"));
    window.setFramerateLimit(60);

    Serum2D::Editor::Editor editor(window);
    editor.run();

    return 0;
}