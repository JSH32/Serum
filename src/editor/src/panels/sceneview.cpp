#include <iostream>
#include "sceneview.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "icons.h"
#include "Serum/components/shape.h"
#include "Serum/math_utils.h"

namespace Serum2D::Editor {
    SceneViewPanel::SceneViewPanel(Core::Scene* scene, Core::Entity& selectedEntity)
        : scene(scene), selectedEntity(selectedEntity) {
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

    void SceneViewPanel::onUpdate() {
        renderTexture.clear(sf::Color(50, 50, 50));
        drawGridLines();
        scene->render(renderTexture);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin(ICON_FA_CAMERA " Scene view");

        setReceiveEvents(ImGui::IsWindowFocused());
        windowContentArea = ImGui::GetContentArea();

        // Resize RenderTexture based on the size of the ImGui window
        float windowWidth = ImGui::GetContentRegionAvail().x;
        float windowHeight = ImGui::GetContentRegionAvail().y;
        if ((uint)windowWidth != renderTexture.getSize().x || (uint)windowHeight != renderTexture.getSize().y) {
            renderTexture.create((uint)windowWidth, (uint)windowHeight);
            sceneView.setSize(windowWidth, windowHeight);
            renderTexture.setView(sceneView);
        }

        if (selectedEntity && selectedEntity.hasComponent<sf::Transformable>()) {
            auto& transform = selectedEntity.getComponent<sf::Transformable>();

            thor::Arrow xArrow;
            xArrow.setColor(sf::Color::Red);
            xArrow.setDirection(100 * zoom, 0);
            xArrow.setThickness(7 * zoom);
            xArrow.setColor(sf::Color::Red);
            xArrow.setPosition(transform.getPosition());
            renderTexture.draw(xArrow);

            xGizmoBounding = sf::FloatRect(sf::Vector2f(transform.getPosition().x, transform.getPosition().y - xArrow.getThickness()),
                                           sf::Vector2f(100 * zoom, 14 * zoom));

            thor::Arrow yArrow;
            yArrow.setColor(sf::Color::Green);
            yArrow.setDirection(0, 100 * zoom);
            yArrow.setThickness(7 * zoom);
            yArrow.setColor(sf::Color::Green);
            yArrow.setPosition(transform.getPosition());
            renderTexture.draw(yArrow);

            yGizmoBounding = sf::FloatRect(sf::Vector2f(transform.getPosition().x - xArrow.getThickness(), transform.getPosition().y),
                                           sf::Vector2f(14 * zoom, 100 * zoom));

            sf::CircleShape center;
            center.setFillColor(sf::Color::Blue);
            center.setRadius(10 * zoom);
            center.setPosition(transform.getPosition());
            center.setOrigin(sf::Vector2f(center.getRadius(), center.getRadius()));

            sf::RectangleShape globalDrag;
            globalDrag.setFillColor(sf::Color(0, 0, 255, 100));
            globalDrag.setSize(sf::Vector2f(50 * zoom, 50 * zoom));
            globalDrag.setOrigin(globalDrag.getOrigin().x + 3.5f * zoom, globalDrag.getOrigin().y + 3.5f * zoom);
            globalDrag.setPosition(transform.getPosition());

            anyBounding = globalDrag.getGlobalBounds();

            renderTexture.draw(center);
            renderTexture.draw(globalDrag);
        }

        ImGui::Image(sf::Sprite(renderTexture.getTexture()));
        ImGui::End();

        ImGui::PopStyleVar();
    }

    void SceneViewPanel::onEvent(sf::Event event) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == 0 && !panning) {
                auto originalMousePos = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);

                auto [windowTopCorner, windowBottomCorner] = windowContentArea;

                // Get a bounding rect of the window content area
                auto windowBounds = sf::FloatRect(sf::Vector2f(windowTopCorner.x, windowTopCorner.y),
                                                    sf::Vector2f(windowBottomCorner.x - windowTopCorner.x, windowBottomCorner.y - windowTopCorner.y));

                // Ignore if click was outside the window
                if (!windowBounds.contains((float)originalMousePos.x, (float)originalMousePos.y))
                    return;

                auto mouseCoords = ImGui::CalculateImOffset(renderTexture, originalMousePos, std::get<0>(windowContentArea));
                if (selectedEntity) {
                    if (xGizmoBounding.contains(mouseCoords)) {
                        transforming = true;
                        dragAxis = DragAxis::Horizontal;
                    } else if (yGizmoBounding.contains(mouseCoords)) {
                        transforming = true;
                        dragAxis = DragAxis::Vertical;
                    } else if (anyBounding.contains(mouseCoords)) {
                        transforming = true;
                        dragAxis = DragAxis::Any;
                    }
                }

                if (transforming) {
                    oldItemPos = selectedEntity.getComponent<sf::Transformable>().getPosition();
                    oldPos = ImGui::CalculateImOffset(renderTexture, originalMousePos, std::get<0>(windowContentArea));
                } else {
                    bool entityClicked = false;

                    scene->registry.each([&](auto entityID) {
                        if (entityClicked) return;
                        Core::Entity entity = { entityID, scene };
                        if (!scene->registry.all_of<sf::Transformable, Core::Components::ShapeComponent>(entityID))
                            return;

                        auto& transform = entity.getComponent<sf::Transformable>();
                        auto& shape = entity.getComponent<Core::Components::ShapeComponent>();

                        sf::Vector2f points[shape.shape->getPointCount()];
                        for (int i = 0; i < shape.shape->getPointCount(); i++) {
                            sf::Transformable shapeTransform(transform);
                            shapeTransform.setOrigin(shape.shape->getOrigin());
                            auto point = shapeTransform.getTransform().transformPoint(shape.shape->getPoint(i));
                            points[i] = point;
                        }

                        // Clicked in the shape
                        if (MathUtils::pointInPolygon(points, (int)shape.shape->getPointCount(),ImGui::CalculateImOffset(renderTexture, sf::Vector2i(
                                event.mouseButton.x, event.mouseButton.y), std::get<0>(windowContentArea)))) {
                            selectedEntity = entity;
                            entityClicked = true;

                            return;
                        }
                    });

                    if (!entityClicked)
                        selectedEntity = {};
                }
            } else if (event.mouseButton.button == 1 && !transforming) {
                panning = true;
                oldPos = ImGui::CalculateImOffset(renderTexture, sf::Vector2i(
                        event.mouseButton.x, event.mouseButton.y), std::get<0>(windowContentArea));
            }
        } else if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == 0)
                transforming = false;
            else if (event.mouseButton.button == 1)
                panning = false;
        } else if (event.type == sf::Event::MouseMoved) {
            if (panning) {
                const sf::Vector2f newPos = ImGui::CalculateImOffset(renderTexture, sf::Vector2i(
                        event.mouseMove.x, event.mouseMove.y), std::get<0>(windowContentArea));

                sceneView.setCenter(sceneView.getCenter() + (oldPos - newPos));
                renderTexture.setView(sceneView);
                oldPos = ImGui::CalculateImOffset(renderTexture, sf::Vector2i(
                        event.mouseMove.x, event.mouseMove.y), std::get<0>(windowContentArea));
            } else if (transforming) {
                const sf::Vector2f position = ImGui::CalculateImOffset(renderTexture, sf::Vector2i(
                        event.mouseMove.x, event.mouseMove.y), std::get<0>(windowContentArea));
                auto& transform = selectedEntity.getComponent<sf::Transformable>();
                if (dragAxis == DragAxis::Horizontal)
                    transform.setPosition(oldItemPos.x + (position.x - oldPos.x), transform.getPosition().y);
                else if (dragAxis == DragAxis::Vertical)
                    transform.setPosition(transform.getPosition().x, oldItemPos.y + (position.y - oldPos.y));
                else if (dragAxis == DragAxis::Any)
                    transform.setPosition(oldItemPos.x + (position.x - oldPos.x), oldItemPos.y + (position.y - oldPos.y));
            }
        } else if (event.type == sf::Event::MouseWheelScrolled) {
            if (!panning) {
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
}