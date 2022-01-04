#include "grid.h"

namespace Serum::Editor {
    Grid::Grid():
            tileSize(sf::Vector2i(50, 50)),
            tileCount(sf::Vector2i(16, 12)),
            position(sf::Vector2i(0, 0)),
            thickness(2.f),
            color(sf::Color(255, 255, 255, 70))
    {
        initialize();
    }

    void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();

        for (auto& line : horizontalLineTable)
            target.draw(line, states);

        for (auto& line : verticalLineTable)
            target.draw(line, states);
    }

    void Grid::initialize() {
        // Create horizontal line
        for(int i= 0; i <= tileCount.y; i++) {
            sf::RectangleShape line;
            line.setSize(sf::Vector2f(tileSize.x * tileCount.x, thickness));
            line.setFillColor(color);
            line.setPosition(sf::Vector2f(0, i * tileSize.y));

            horizontalLineTable.push_back(line);
        }

        // create vertical line
        for (int i=0; i <= tileCount.x; i++) {
            sf::RectangleShape line;
            line.setSize(sf::Vector2f(thickness, tileSize.y * tileCount.y));
            line.setFillColor(color);
            line.setPosition(sf::Vector2f(i * tileSize.x, 0));

            verticalLineTable.push_back(line);
        }
    }

    void Grid::updatePosition(const sf::Vector2i& newPosition) {
        sf::Vector2f result;

        result.x = (newPosition.x - newPosition.x) * tileSize.x;
        result.y = (newPosition.y - newPosition.y) * tileSize.y;

        for(auto& line : horizontalLineTable)
            line.move(result);

        for(auto& line : verticalLineTable)
            line.move(result);

        position = newPosition;
    }

    sf::Vector2f Grid::getCenter() {
        sf::Vector2f center;

        center.x = horizontalLineTable.at(0).getPosition().x + horizontalLineTable.at(0).getSize().x/2.f;
        center.y = verticalLineTable.at(0).getPosition().y + verticalLineTable.at(0).getSize().y/2.f;

        return center;
    }

    void Grid::update(const sf::Vector2i& newTileSize, const sf::Vector2i& newTileCount) {
        tileSize = newTileSize;
        tileCount = newTileCount;

        horizontalLineTable.clear();
        verticalLineTable.clear();

        initialize();
        updatePosition(position);
    }

    const sf::Vector2i& Grid::getTileSize() const {
        return tileSize;
    }

    const sf::Vector2i& Grid::getTileCount() const {
        return tileCount;
    }

    const sf::Vector2i& Grid::getPosition() const {
        return position;
    }

    void Grid::setColor(const sf::Color& newColor)
    {
        color = newColor;

        initialize();
        update(tileSize, tileCount);
        updatePosition(position);
    }

    sf::Color Grid::getColor() {
        return color;
    }
}