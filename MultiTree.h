//
// Created by kamil-hp on 13.09.22.
//

#ifndef MAIN_CPP_MULTITREE_H
#define MAIN_CPP_MULTITREE_H

#include <optional>
#include <set>
#include "Point.h"

class multiTreecomparsionX // not something like : Compare  ???
{
public:
    bool operator() (const Edge& lhs, const Edge& rhs) const
    {
        if(lhs.first.x != rhs.first.x)
            return lhs.first.x < rhs.first.x;
        else if(lhs.second.x != rhs.second.x)
            return lhs.second.x < rhs.second.x;
        else if(lhs.first.y != rhs.first.y)
            return lhs.first.y < rhs.first.y;
        return lhs.second.y < rhs.second.y;
    }
};

class MultiTreeX {
    //always isX
public:
    void insert(const Edge& s);
    void remove(const Edge& s);
    std::optional<Edge> prev(const Edge& s);
    std::optional<Edge> next(const Edge& s);
    [[nodiscard]] std::size_t getSize() const {
        return tree.size();
        //return isX ? treeX.getSize() : treeY.getSize();
    }
    std::set<Edge, multiTreecomparsionX> tree;
private:
};

void MultiTreeX::insert(const Edge &s) {
    tree.insert(s);
}

void MultiTreeX::remove(const Edge &s) {
    tree.erase(s);
}

std::optional<Edge> MultiTreeX::next(const Edge &s) {
    auto it = tree.lower_bound(s);
    if(it==tree.end())
        return std::nullopt;
    ++it;
    if(it==tree.end())
        return std::nullopt;
    else
        return *it;
}

std::optional<Edge> MultiTreeX::prev(const Edge &s) {
    auto it = tree.lower_bound(s);
    if(it==tree.end() || it==tree.begin())
        return std::nullopt;
    --it;
    return *it;
}


#endif //MAIN_CPP_MULTITREE_H
