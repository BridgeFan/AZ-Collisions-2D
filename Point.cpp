//
// Created by kamil-hp on 04.06.22.
//
#include "Point.h"
std::vector <Edge> toEdges(const std::vector <Point> &p) {
    std::vector<Edge> e;
    for(int i=0;i<p.size();i++) {
        e.emplace_back(p[i],p[(i+1)%p.size()]);
    }
    return e;
}
