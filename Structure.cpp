//
// Created by Kamil-XKOM on 27.05.2022.
//

#include "Structure.h"
const std::vector<Point>* Structure::p1 = nullptr;
const std::vector<Point>* Structure::p2 = nullptr;
std::pair<Structure, Structure> Structure::getNewPoints(bool isFirst, unsigned int index, bool isX) {
    auto& p = isFirst ? (*p1) : (*p2);
    Structure s1, s2;
    unsigned next = (index+1)%(p.size());
    auto val1 = isX ? p[index].x : p[index].y;
    auto val2= isX ? p[next].x : p[next].y;
    if(val1 < val2) {
        s1 = {isFirst, index, Left, true};
        s2 = {isFirst, next, Right, false};
    }
    else if(val2 < val1) {
        s1 = {isFirst, index, Right, true};
        s2 = {isFirst, next, Left, false};
    }
    else {
        s1 = {isFirst, index, Vertical, true};
        s2 = {isFirst, next, Vertical, false};
    }
    return std::make_pair(s1,s2);
}

Point Structure::getPoint() const {
    auto& p = isFirst ? (*p1) : (*p2);
    return p[index];
}

Edge Structure::asEdge() const {
    auto& p = isFirst ? (*p1) : (*p2);
    if(!isFirstOnPolygon)
        return {p[(index+p.size()-1)%p.size()],p[index]};
    else
        return {p[index], p[(index+1)%p.size()]};
}