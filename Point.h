//
// Created by Kamil-XKOM on 03.05.2022.
//

#ifndef AZ_COLLISIONS2D_POINT_H
#define AZ_COLLISIONS2D_POINT_H
#include <utility>
#include <vector>

struct Point {
    double x;
    double y;
    unsigned char polygon; //polygon to which the point belongs

    bool operator==(const Point &rhs) const {
        return x == rhs.x &&
               y == rhs.y;
    }
    bool operator!=(const Point &rhs) const {return !(rhs == *this);}
    Point& operator =(const Point& b) {
        if(this==&b)
            return *this;
        x=b.x;
        y=b.y;
        polygon=b.polygon;
        return *this;
    }
};

typedef std::pair<Point, Point> Edge;

std::vector<Edge> toEdges(const std::vector<Point>& p);

#endif //AZ_COLLISIONS2D_POINT_H
