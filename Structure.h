//
// Created by Kamil-XKOM on 27.05.2022.
//

#ifndef AZ_COLLISIONS2D_STRUCTURE_H
#define AZ_COLLISIONS2D_STRUCTURE_H

#include <vector>
#include "Point.h"

enum StructureType {
    Left=0,
    Right=1,
    Vertical=2
};

struct Structure {
    static const std::vector<Point> *p1, *p2;
    bool isFirst;
    bool isFirstOnPolygon;
    unsigned index;
    unsigned short type; //0-left, 1-right, 2-vertical
    [[nodiscard]] Point getPoint() const;
    [[nodiscard]] Edge asEdge() const;
    Structure(bool isFirst, unsigned int index, unsigned short type, bool isFirstOnPolygon) : isFirst(isFirst), index(index), type(type), isFirstOnPolygon(isFirstOnPolygon) {}
    Structure() = default;
    static std::pair<Structure, Structure> getNewPoints(bool isFirst, unsigned index, bool isX);
};

#endif //AZ_COLLISIONS2D_STRUCTURE_H
