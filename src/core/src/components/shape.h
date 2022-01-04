#pragma once;

#include <memory>
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

namespace Serum2D::Core::Components {
    enum ShapeType {
        Circle,
        Rectangle
    };

    class ShapeComponent : public sf::Drawable {
    public:
        ShapeComponent();

        void SetShape(ShapeType shapeType);
        ShapeType GetShape() { return shapeType; }

        sf::Color GetFillColor();
        void SetFillColor(sf::Color color);
    protected:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    private:
        ShapeType shapeType = ShapeType::Rectangle;
        std::unique_ptr<sf::Shape> shape = nullptr;
//        explicit TagComponent(std::string tag) : tag(std::move(tag)) {}
    //    TagComponent() = default;
  //      TagComponent(const TagComponent&) = default;

    //    std::string tag;
    };
}