#include <iostream>
#include "sceneview.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "icons.h"

namespace Serum2D::Editor {
    SceneViewPanel::SceneViewPanel(Core::Scene* scene) : scene(scene) {
        gridLineY.setFillColor(sf::Color::Green);
        gridLineX.setFillColor(sf::Color::Red);
        renderTexture.setView(sceneView);
    }

    void SceneViewPanel::drawGridLines() {
        auto relativeViewCoords = renderTexture.mapPixelToCoords(sf::Vector2i(0.f, 0.f), sceneView);
        gridLineY.setPosition(sf::Vector2f(relativeViewCoords.x, 0));
        gridLineY.setSize(sf::Vector2f(sceneView.getSize().x, 2));
        renderTexture.draw(gridLineY);

        gridLineX.setPosition(sf::Vector2f(0, relativeViewCoords.y));
        gridLineX.setSize(sf::Vector2f(2, sceneView.getSize().y));
        renderTexture.draw(gridLineX);
    }

    void SceneViewPanel::onEvent(sf::Event event) {
//        else if (event.mouseButton.button == 0) {
//            auto pos = renderTexture.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, -event.mouseButton.y));
//            sf::RectangleShape r(sf::Vector2f(30, 30));
//            r.setPosition(pos);
//            renderTexture.draw(r);
//            std::cout << "hi" << std::endl;
//        }
//        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
//            auto pos = renderTexture.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
//            std::cout << pos.x << std::endl;
//            std::cout << pos.y << std::endl;
//            sf::RectangleShape r(sf::Vector2f(30, 30));
//            r.setPosition(pos);
//            r.setFillColor(sf::Color::Red);
//            renderTexture.draw(r);
//        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == 1) {
                moving = true;
                oldPos = renderTexture.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, -event.mouseButton.y));
            }
        } else if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == 1)
                moving = false;
        } else if (event.type == sf::Event::MouseMoved) {
            if (moving) {
                const sf::Vector2f newPos = renderTexture.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, -event.mouseMove.y));
                const sf::Vector2f deltaPos = oldPos - newPos;

                sceneView.setCenter(sceneView.getCenter() + deltaPos);
                renderTexture.setView(sceneView);
                oldPos = renderTexture.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, -event.mouseMove.y));
            }
        } else if (event.type == sf::Event::MouseWheelScrolled) {
            if (!moving) {
                if (event.mouseWheelScroll.delta <= -1)
                    zoom = std::min(2.f, zoom + .1f);
                else if (event.mouseWheelScroll.delta >= 1)
                    zoom = std::max(.5f, zoom - .1f);

                sceneView.setSize(renderTexture.getDefaultView().getSize());
                sceneView.zoom(zoom);
                renderTexture.setView(sceneView);
            }
        }
    }

    void SceneViewPanel::onUpdate() {
        renderTexture.clear(sf::Color(50, 50, 50));
        drawGridLines();
        scene->render(renderTexture);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin(ICON_FA_VIDEO_CAMERA " Scene view");

        float windowWidth = ImGui::GetContentRegionAvail().x;
        float windowHeight = ImGui::GetContentRegionAvail().y;
        if ((uint)windowWidth != renderTexture.getSize().x || (uint)windowHeight != renderTexture.getSize().y) {
            renderTexture.create((uint)windowWidth, (uint)windowHeight);
            sceneView.setSize(windowWidth, windowHeight);
            renderTexture.setView(sceneView);
        }

        ImGui::Image(sf::Sprite(renderTexture.getTexture()));
        setReceiveEvents(ImGui::IsWindowFocused());
        ImGui::End();

        ImGui::PopStyleVar();
    }
}