#include "shape.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

namespace Serum2D::Core::Components {
    ShapeComponent::ShapeComponent(const ShapeType shapeType) : shapeType(shapeType) {
        setShape(shapeType);
    }

    void ShapeComponent::draw(sf::RenderTarget &target, const sf::RenderStates states) const {
        target.draw(*shape, states);
    }

    void ShapeComponent::setShape(const ShapeType newShapeType) {
        shapeType = newShapeType;
        std::unique_ptr<sf::Shape> newShape = nullptr;

        switch (shapeType) {
            case ShapeType::Rectangle: {
                auto rectShape = std::make_unique<sf::RectangleShape>();
                rectShape->setSize(sf::Vector2f(50, 50));
                rectShape->setOrigin(sf::Vector2f(50.f / 2, 50.f / 2));
                newShape = std::move(rectShape);
                break;
            }
            case ShapeType::Circle: {
                auto circleShape = std::make_unique<sf::CircleShape>();
                circleShape->setRadius(25);
                circleShape->setOrigin(sf::Vector2f(circleShape->getRadius(), circleShape->getRadius()));
                newShape = std::move(circleShape);
                break;
            }
        }

        // Shape already existed before, move over properties
        if (shape != nullptr) {
            newShape->setOutlineColor(shape->getOutlineColor());
            newShape->setFillColor(shape->getFillColor());
            newShape->setRotation(shape->getRotation());
        }

        shape = std::move(newShape);
    }
}
