#ifndef TILE_HPP
#define TILE_HPP

#include <string>
#include <vector>
#include <iostream>

#include "Resource.hpp"
#include "Node.hpp"

using namespace std;

class Node;

class Tile
{
    int id;
    int number;
    Resource resource; 
    vector<Node *> nodes;

public:
    Tile(int i, int num, Resource res);
    ~Tile() = default;

    void addNodes(const vector<Node *> &nodes2);

    int getNumber() const;
    Resource getResource() const;
    int getId() const;
    vector<size_t> getNodes() ;
};

#endif // TILE_HPP

