#pragma once

#include "SFML/System/Vector2.hpp"

namespace Serum2D::MathUtils {
    /**
     * Given three collinear points p, q, r, the function checks if
     * point q lies on line segment 'pr'
     */
    bool onSegment(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r);

    /**
     * To find orientation of ordered triplet (p, q, r).
     * The function returns following values
     * 1 -> Clockwise
     * 2 -> Counterclockwise
     */
    float orientationTriplet(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r);

    /**
     * The function that returns true if line segment 'p1q1' one 'p2q2' intersect
     */
    bool doIntersect(sf::Vector2f p1, sf::Vector2f q1, sf::Vector2f p2, sf::Vector2f q2);

    /**
     * Returns true if the point p lies inside the polygon[] with n vertices
     */
    bool pointInPolygon(sf::Vector2f polygon[], int n, sf::Vector2f p);
}