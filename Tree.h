//
// Created by Kamil-XKOM on 03.05.2022.
//

#ifndef AZ_COLLISIONS2D_TREE_H
#define AZ_COLLISIONS2D_TREE_H

#include <optional>
#include <set>
#include "Point.h"

class treecomparsionX // not something like : Compare  ???
{
public:
    bool operator() (const Edge& lhs, const Edge& rhs) const
    {
        return lhs.first.x < rhs.first.x;
    }
};

class treecomparsionY // not something like : Compare  ???
{
public:
    bool operator() (const Edge& lhs, const Edge& rhs) const
    {
        return lhs.first.y < rhs.first.y;
    }
};

class Tree {
private:
    const bool isX;
public:
    void insert(const Edge& s);
    void remove(const Edge& s);
    std::optional<Edge> prev(const Edge& s);
    std::optional<Edge> next(const Edge& s);
    explicit Tree(bool isX): isX(isX) {}
    [[nodiscard]] int getSize() const {
        return isX ? treeX.size() : treeY.size();
        //return isX ? treeX.getSize() : treeY.getSize();
    }
private:
    std::set<Edge, treecomparsionX> treeX;
    std::set<Edge, treecomparsionY> treeY;
};

void Tree::insert(const Edge &s) {
    isX ? treeX.insert(s) : treeY.insert(s);
}

void Tree::remove(const Edge &s) {
    isX ? treeX.erase(s) : treeY.erase(s);
}

std::optional<Edge> Tree::next(const Edge &s) {
    if(isX) {
        auto it = treeX.upper_bound(s);
        if(it==treeX.end())
            return std::nullopt;
        else
            return *it;
    }
    else {
        auto it = treeY.upper_bound(s);
        if(it==treeY.end())
            return std::nullopt;
        else
            return *it;
    }
}

std::optional<Edge> Tree::prev(const Edge &s) {
    if(isX) {
        auto it = treeX.lower_bound(s);
        if(it==treeX.end() || it==treeX.begin())
            return std::nullopt;
        --it;
        return *it;
    }
    else {
        auto it = treeY.lower_bound(s);
        if(it==treeY.end() || it==treeY.begin())
            return std::nullopt;
        --it;
        return *it;
    }
}


#endif //AZ_COLLISIONS2D_TREE_H
