#pragma once

#include <memory>
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTexture.hpp"

namespace Serum::Editor {
    class Grid : public sf::Transformable, public sf::Drawable {
    public:
        Grid();
        sf::Vector2f getCenter();
        void update(const sf::Vector2i& tileSize, const sf::Vector2i& tileCount);
        void updatePosition(const sf::Vector2i& position);
        const sf::Vector2i& getTileSize() const;
        const sf::Vector2i& getTileCount() const;
        const sf::Vector2i& getPosition() const;
        void setColor(const sf::Color& color);
        sf::Color getColor();
    private:
        void initialize();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    private:
        sf::Vector2i tileSize;
        sf::Vector2i tileCount;
        sf::Vector2i position;
        sf::Color color;
        float thickness;
        std::vector<sf::RectangleShape> horizontalLineTable;
        std::vector<sf::RectangleShape>  verticalLineTable;
    };
}