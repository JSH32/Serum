#include "sceneview.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "fontawesome5.h"
#include "imguiutils.h"
#include "Serum/components/shape.h"
#include "Serum/mathutils.h"
#include "Thor/Shapes/Arrow.hpp"
#include "imgui-SFML.h"

namespace Serum2D::Editor {
    SceneViewPanel::SceneViewPanel(Core::Scene* scene, Core::Entity& selectedEntity)
        : selectedEntity(selectedEntity), scene(scene) {
        gridLineY.setFillColor(sf::Color::Green);
        gridLineX.setFillColor(sf::Color::Red);
        renderTexture.setView(sceneView);
    }

    void SceneViewPanel::drawGridLines() {
	    const auto relativeViewCoords = renderTexture.mapPixelToCoords(sf::Vector2i(0.f, 0.f), sceneView);
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
        const ImVec2 windowSize = ImGui::GetContentRegionAvail();
        if ((unsigned int)windowSize.x != renderTexture.getSize().x || (unsigned int)windowSize.y != renderTexture.getSize().y) {
            renderTexture.create((unsigned int)windowSize.x, (unsigned int)windowSize.y);
            sceneView.setSize(windowSize.x, windowSize.y);
            renderTexture.setView(sceneView);
        }

        if (selectedEntity && selectedEntity.hasComponent<sf::Transformable>()) {
            if (transformType == TransformType::Position)
                updateTransformPositionGizmo(selectedEntity.getComponent<sf::Transformable>());
            else if (transformType == TransformType::Scale)
                updateTransformScaleGizmo(selectedEntity.getComponent<sf::Transformable>());
        }

        ImGui::Image(sf::Sprite(renderTexture.getTexture()));
        ImGui::End();

        ImGui::PopStyleVar();
    }

    void SceneViewPanel::updateTransformPositionGizmo(const sf::Transformable& transform) {
		thor::Arrow xArrow;
		xArrow.setColor(widgetRed);
		xArrow.setDirection(100 * zoom, 0);
		xArrow.setThickness(7 * zoom);
		xArrow.setPosition(transform.getPosition());
		renderTexture.draw(xArrow);

		xGizmoBounding = sf::FloatRect(sf::Vector2f(transform.getPosition().x, transform.getPosition().y - xArrow.getThickness()),
		                               sf::Vector2f(100 * zoom, 14 * zoom));

		thor::Arrow yArrow;
		yArrow.setColor(widgetGreen);
		yArrow.setDirection(0, 100 * zoom);
		yArrow.setThickness(7 * zoom);
		yArrow.setPosition(transform.getPosition());
		renderTexture.draw(yArrow);

		yGizmoBounding = sf::FloatRect(sf::Vector2f(transform.getPosition().x - yArrow.getThickness(), transform.getPosition().y),
		                               sf::Vector2f(14 * zoom, 100 * zoom));

		sf::CircleShape center;
		center.setFillColor(widgetBlue);
		center.setRadius(10 * zoom);
		center.setPosition(transform.getPosition());
		center.setOrigin(sf::Vector2f(center.getRadius(), center.getRadius()));

		sf::RectangleShape globalDrag;
		globalDrag.setFillColor(sf::Color(widgetBlue.r, widgetBlue.g, widgetBlue.b, 100));
		globalDrag.setSize(sf::Vector2f(50 * zoom, 50 * zoom));
		globalDrag.setOrigin(globalDrag.getOrigin().x + 3.5f * zoom, globalDrag.getOrigin().y + 3.5f * zoom);
		globalDrag.setPosition(transform.getPosition());

		anyBounding = globalDrag.getGlobalBounds();

		renderTexture.draw(center);
		renderTexture.draw(globalDrag);
    }

    void SceneViewPanel::updateTransformScaleGizmo(const sf::Transformable& transform) {
        sf::RectangleShape yShape;
        yShape.setFillColor(sf::Color::Green);
        yShape.setSize(sf::Vector2f(7 * zoom, 80 * zoom));
        yShape.setPosition(transform.getPosition());
        yShape.setOrigin(sf::Vector2f(yShape.getOrigin().x + 3.5f * zoom, yShape.getOrigin().y));
        renderTexture.draw(yShape);

        sf::RectangleShape ySquare;
        ySquare.setFillColor(sf::Color::Green);
        ySquare.setSize(sf::Vector2f(20 * zoom, 20 * zoom));
    	ySquare.setOrigin(sf::Vector2f(ySquare.getOrigin().x + 10.f * zoom, ySquare.getOrigin().y));
        ySquare.setPosition(sf::Vector2f(transform.getPosition().x, transform.getPosition().y + 80 * zoom));
        renderTexture.draw(ySquare);

        yGizmoBounding = sf::FloatRect(sf::Vector2f(transform.getPosition().x - 10, transform.getPosition().y),
                               sf::Vector2f(20 * zoom, 100 * zoom));

    	sf::RectangleShape xShape;
        xShape.setFillColor(sf::Color::Red);
        xShape.setSize(sf::Vector2f(80 * zoom, 7 * zoom));
        xShape.setPosition(transform.getPosition());
        xShape.setOrigin(sf::Vector2f(xShape.getOrigin().x, xShape.getOrigin().y + 3.5f * zoom));
        renderTexture.draw(xShape);

    	sf::RectangleShape xSquare;
        xSquare.setFillColor(sf::Color::Red);
        xSquare.setSize(sf::Vector2f(20 * zoom, 20 * zoom));
    	xSquare.setOrigin(sf::Vector2f(xSquare.getOrigin().x, xSquare.getOrigin().y + 10.f * zoom));
        xSquare.setPosition(sf::Vector2f(transform.getPosition().x + 80 * zoom, transform.getPosition().y));
        renderTexture.draw(xSquare);

        xGizmoBounding = sf::FloatRect(sf::Vector2f(transform.getPosition().x, transform.getPosition().y - 10),
                       sf::Vector2f(100 * zoom, 20 * zoom));

        // Center square, scale entire shape
        sf::RectangleShape centerScale;
        centerScale.setPosition(transform.getPosition());
        centerScale.setFillColor(sf::Color(128, 128, 128, 255));
        centerScale.setSize((sf::Vector2f(25 * zoom, 25 * zoom)));
        centerScale.setOrigin(centerScale.getSize().x / 2.f, centerScale.getSize().y / 2.f);
        renderTexture.draw(centerScale);
    }

    void SceneViewPanel::onEvent(const sf::Event event) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == 0 && !panning) {
	            const auto originalMousePos = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);

                auto [windowTopCorner, windowBottomCorner] = windowContentArea;

                // Get a bounding rect of the window content area
	            const auto windowBounds = sf::FloatRect(sf::Vector2f(windowTopCorner.x, windowTopCorner.y),
	                                                    sf::Vector2f(windowBottomCorner.x - windowTopCorner.x, windowBottomCorner.y - windowTopCorner.y));

                // Ignore if click was outside the window
                if (!windowBounds.contains((float)originalMousePos.x, (float)originalMousePos.y))
                    return;

	            const auto mouseCoords = ImGui::CalculateImOffset(
		            renderTexture, originalMousePos, std::get<0>(windowContentArea));

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

                    scene->registry.each([&](auto entityId) {
                        if (entityClicked) return;
                        Core::Entity entity = { entityId, scene };
                        if (!scene->registry.all_of<sf::Transformable, Core::Components::ShapeComponent>(entityId))
                            return;

                        const auto& transform = entity.getComponent<sf::Transformable>();
                        const auto& shape = entity.getComponent<Core::Components::ShapeComponent>();

                        std::vector<sf::Vector2f> points(shape.shape->getPointCount());
                        for (int i = 0; i < shape.shape->getPointCount(); i++) {
                            sf::Transformable shapeTransform(transform);
                            shapeTransform.setOrigin(shape.shape->getOrigin());
                            const auto point = shapeTransform.getTransform().transformPoint(shape.shape->getPoint(i));
                            points[i] = point;
                        }

                        // Clicked in the shape
                        if (MathUtils::pointInPolygon(&points[0], (int)shape.shape->getPointCount(), ImGui::CalculateImOffset(renderTexture, sf::Vector2i(
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
