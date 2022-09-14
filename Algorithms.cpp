//
// Created by Kamil-XKOM on 03.05.2022.
//
#include <cmath>
#include <algorithm>
#include "Algorithms.h"
#include "Structure.h"
#include "Tree.h"
#include "MultiTree.h"
#include <iostream>
#include <list>

double d(const Point &u, const Point &v) {
    return std::sqrt((u.x-v.x)*(u.x-v.x)+(u.y-v.y)*(u.y-v.y));
}

double det(const Point &u, const Point &v, const Point &w) {
    return u.x*v.y + u.y*w.x + v.x*w.y - w.x*v.y - w.y*u.x - v.x*u.y;
}

bool onEdge(const Point &v1, const Point &v2, const Point &v3) {
    return std::min(v1.x,v2.x)<=v3.x && v3.x<=std::max(v1.x,v2.x) &&
           std::min(v1.y,v2.y)<=v3.y && v3.y<=std::max(v1.y,v2.y);
}

bool areEdgesIntersecting(const Edge& e1, const Edge& e2) {
    auto && [v1, v2] = e1;
    auto && [v3, v4] = e2;
    if(v1.polygon==v3.polygon)
        return false;
    double d1 = det(v3,v4,v1);
    double d2 = det(v3,v4,v2);
    double d3 = det(v1,v2,v3);
    double d4 = det(v1,v2,v4);
    if(d1*d2<0 && d3*d4<0)
        return true;
    if(d1==0 && onEdge(v3,v4,v1))
        return true;
    if(d2==0 && onEdge(v3,v4,v2))
        return true;
    if(d3==0 && onEdge(v1,v2,v3))
        return true;
    if(d4==0 && onEdge(v1,v2,v4))
        return true;
    return false;
}

bool arePolygonsIntersecting(const std::vector<Point>&w1, const std::vector<Point> &w2, bool isX) {
    Structure::p1 = &w1;
    Structure::p2 = &w2;
    Tree T(isX);
    std::vector<Structure> structure;
    for(unsigned i=0;i<w1.size();i++) {
        auto [p1, p2] = Structure::getNewPoints(true, i, isX);
        structure.push_back(p1);
        structure.push_back(p2);
    }
    for(unsigned i=0;i<w2.size();i++) {
        auto [p1, p2] = Structure::getNewPoints(false, i, isX);
        structure.push_back(p1);
        structure.push_back(p2);
    }
    if(isX)
        std::sort(structure.begin(), structure.end(), [](const Structure& a, const Structure& b) {
                      return a.getPoint().x < b.getPoint().x;
                  }
        );
    else
        std::sort(structure.begin(), structure.end(), [](const Structure& a, const Structure& b) {
                      return a.getPoint().y < b.getPoint().y;
                  }
        );
    for(auto str: structure) {
        auto s = str.asEdge();
        if(str.type == Left) {
            T.insert(s);
            auto s_p = T.prev(s);
            auto s_n = T.next(s);
            if(s_p.has_value() && areEdgesIntersecting(s, s_p.value()))
                return true;
            if(s_n.has_value() && areEdgesIntersecting(s, s_n.value()))
                return true;
        }
        if(str.type == Right) {
            auto s_p = T.prev(s);
            auto s_n = T.next(s);
            if(s_p.has_value() && s_n.has_value() && areEdgesIntersecting(*s_p,*s_n))
                return true;
            T.remove(s);
        }
    }
    return false;
}


void addPoint(std::vector<Edge>& edges, const Edge& edge) {
    Edge e2;
    e2 = edge;
    if(edge.first.x>edge.second.x || edge.first.y>edge.second.y)
        std::swap(e2.first, e2.second);
    edges.push_back(e2);
}

bool pointComparer(const Point& p1, const Point& p2) {
    if(p1.x!=p2.x) return p1.x<p2.x;
    return p1.y<p2.y;
}

bool areTrilinearHV(const Edge& e1, const Edge& e2) {
    if(e1.second!=e2.first)
        return false;
    if(e1.first.x!=e2.second.x && e1.first.y!=e2.second.y)
        return false;
    return true;
}

bool checkMergeEdges(Edge& edge, const Edge& e2, bool areReversed=false) {
    if(!areReversed && !areTrilinearHV(edge,e2))
        return false;
    if(areReversed && !areTrilinearHV(e2,edge))
        return false;
    std::initializer_list<Point> initList = {edge.first, edge.second, e2.first, e2.second};
    Point small = std::min(initList, pointComparer);
    Point great = std::max(initList, pointComparer);
    return true;
}

bool horizontal_vertical_intersection(const std::vector<Edge>& first_edges, const std::vector<Edge>& second_edges) {
    std::vector<Edge> firstHVEdges, secondHVEdges;
    for(const auto& e: first_edges) {
        if(e.first.x==e.second.x || e.first.y==e.second.y) {
            if(firstHVEdges.empty() || !checkMergeEdges(firstHVEdges.back(),e))
                firstHVEdges.push_back(e);
        }
    }
    if(firstHVEdges.size()>=2 && checkMergeEdges(*firstHVEdges.begin(), firstHVEdges.back(), true)) {
        firstHVEdges.pop_back();
    }

    for(const auto& e: second_edges) {
        if(e.first.x==e.second.x || e.first.y==e.second.y) {
            if(secondHVEdges.empty() || !checkMergeEdges(secondHVEdges.back(),e))
                secondHVEdges.push_back(e);
        }
    }
    if(secondHVEdges.size()>=2 && checkMergeEdges(*secondHVEdges.begin(), secondHVEdges.back(), true)) {
        secondHVEdges.pop_back();
    }
    for(const auto& e1: first_edges) {
        for(const auto& e2: second_edges) {
            if(areEdgesIntersecting(e1,e2))
                return true;
        }
    }
    return false;
}