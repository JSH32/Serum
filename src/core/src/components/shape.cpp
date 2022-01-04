#include <iostream>
#include "shape.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/CircleShape.hpp"

namespace Serum2D::Core::Components {
    ShapeComponent::ShapeComponent() {
        SetShape(ShapeType::Circle);
    }

    void ShapeComponent::SetShape(ShapeType newShapeType) {
        shapeType = newShapeType;
        std::unique_ptr<sf::Shape> newShape = nullptr;
        switch (newShapeType) {
            case ShapeType::Rectangle:
                newShape = std::make_unique<sf::RectangleShape>();
                ((sf::RectangleShape*)newShape.get())->setSize(sf::Vector2f(1, 1));
                break;
            case ShapeType::Circle:
                newShape = std::make_unique<sf::CircleShape>();
                ((sf::CircleShape*)newShape.get())->setRadius(1);
                break;
        }

        if (shape != nullptr) {
            newShape->setFillColor(shape->getFillColor());
            newShape->setOutlineColor(shape->getOutlineColor());
            newShape->setOutlineThickness(shape->getOutlineThickness());
        } else {
            newShape->setFillColor(sf::Color::Red);
        }

        shape = std::move(newShape);
    }

    void ShapeComponent::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        target.draw(*shape, states);
    }

    sf::Color ShapeComponent::GetFillColor() {
        return shape->getFillColor();
    }

    void ShapeComponent::SetFillColor(sf::Color color) {
        shape->setFillColor(color);
    }
}