#pragma once

#include <memory>
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Shape.hpp"

namespace Serum2D::Core::Components {
    enum class ShapeType {
        Circle,
        Rectangle
    };

    class ShapeComponent final : public sf::Drawable {
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