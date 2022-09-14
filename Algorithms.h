//
// Created by Kamil-XKOM on 03.05.2022.
//

#ifndef AZ_COLLISIONS2D_ALGORITHMS_H
#define AZ_COLLISIONS2D_ALGORITHMS_H

#include <vector>
#include <list>
#include "Point.h"

double det(const Point& u, const Point& v, const Point& w);
double d(const Point& u, const Point& v);
bool onEdge(const Point& v1, const Point& v2, const Point& v3);

bool areEdgesIntersecting (const Edge& e1, const Edge& e2);
bool arePolygonsIntersecting(const std::vector<Point>& w1, const std::vector<Point>& w2, bool isX);

struct Event {
    double y;
    Edge e;
};

bool horizontal_vertical_intersection(const std::vector<Edge>& first_edges, const std::vector<Edge>& second_eges);
#endif //AZ_COLLISIONS2D_ALGORITHMS_H
