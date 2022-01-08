#pragma once

#include <memory>
#include <functional>
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "Serum/log.h"
#include "SFML/Graphics/CircleShape.hpp"

namespace Serum2D::Core::Components {
    enum ShapeType {
        Circle,
        Rectangle
    };

    class ShapeComponent : public sf::Drawable {
    public:
        explicit ShapeComponent(ShapeType shapeType);

        /**
         * Recreate the internal shape with a new type, this will attempt to transfer over shape properties
         */
        void setShape(ShapeType newShapeType);

        ShapeType shapeType;
        std::unique_ptr<sf::Shape> shape;
    protected:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}