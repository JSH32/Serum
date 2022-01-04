#include "sceneview.h"

namespace Serum2D::Editor {
    SceneViewPanel::SceneViewPanel() {
        gridLineY.setFillColor(sf::Color::Green);
        gridLineX.setFillColor(sf::Color::Red);
        renderTexture.setView(sceneView);
    }

    void SceneViewPanel::processEvent(sf::Event event) {
        if (!focus) return;

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

    void SceneViewPanel::update() {
        renderTexture.clear(sf::Color(50, 50, 50));
        drawGridLines();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("Scene view");

        float windowWidth = ImGui::GetContentRegionAvail().x;
        float windowHeight = ImGui::GetContentRegionAvail().y;
        if ((uint)windowWidth != renderTexture.getSize().x || (uint)windowHeight != renderTexture.getSize().y) {
            renderTexture.create((uint)windowWidth, (uint)windowHeight);
            sceneView.setSize(windowWidth, windowHeight);
            renderTexture.setView(sceneView);
        }

        ImGui::Image(sf::Sprite(renderTexture.getTexture()));
        focus = ImGui::IsWindowFocused();
        // ImGui::
        ImGui::End();

        ImGui::PopStyleVar();
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
}