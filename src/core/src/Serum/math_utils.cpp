#include "math_utils.h"

#include <algorithm>

#define INF 10000

namespace Serum2D::MathUtils {
    bool onSegment(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r) {
        if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
            q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
            return true;
        return false;
    }

    float orientationTriplet(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r) {
        float val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

        if (val == 0) return 0; // collinear
        return (val > 0)? 1: 2; // clock or counterclockwise
    }

    bool doIntersect(sf::Vector2f p1, sf::Vector2f q1, sf::Vector2f p2, sf::Vector2f q2) {
        // Find the four orientations needed for general and
        // special cases
        float o1 = orientationTriplet(p1, q1, p2);
        float o2 = orientationTriplet(p1, q1, q2);
        float o3 = orientationTriplet(p2, q2, p1);
        float o4 = orientationTriplet(p2, q2, q1);

        // General case
        if (o1 != o2 && o3 != o4)
            return true;

        // Special Cases
        // p1, q1 and p2 are collinear and p2 lies on segment p1q1
        if (o1 == 0 && onSegment(p1, p2, q1)) return true;

        // p1, q1 and p2 are collinear and q2 lies on segment p1q1
        if (o2 == 0 && onSegment(p1, q2, q1)) return true;

        // p2, q2 and p1 are collinear and p1 lies on segment p2q2
        if (o3 == 0 && onSegment(p2, p1, q2)) return true;

        // p2, q2 and q1 are collinear and q1 lies on segment p2q2
        if (o4 == 0 && onSegment(p2, q1, q2)) return true;

        return false; // Doesn't fall in any of the above cases
    }

    bool pointInPolygon(sf::Vector2f polygon[], int n, sf::Vector2f p) {
        // There must be at least 3 vertices in polygon[]
        if (n < 3) return false;

        // Create a point for line segment from p to infinite
        sf::Vector2f extreme(INF, p.y);

        // Count intersections of the above line with sides of polygon
        int count = 0, i = 0;
        do {
            int next = (i+1)%n;

            // Check if the line segment from 'p' to 'extreme' intersects
            // with the line segment from 'polygon[i]' to 'polygon[next]'
            if (doIntersect(polygon[i], polygon[next], p, extreme)) {
                // If the point 'p' is collinear with line segment 'i-next',
                // then check if it lies on segment. If it lies, return true,
                // otherwise false
                if (orientationTriplet(polygon[i], p, polygon[next]) == 0)
                    return onSegment(polygon[i], p, polygon[next]);

                count++;
            }
            i = next;
        } while (i != 0);

        // Return true if count is odd, false otherwise
        return count&1; // Same as (count%2 == 1)
    }
}