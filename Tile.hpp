// minnesav@gmail.com

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
    Tile(int i, int num, Resource res); // Constructor
    ~Tile() = default; // Destructor

    void addNodes(const vector<Node *> &nodes2); // Add nodes to the tile

    int getNumber() const; // Get the number of the tile
    Resource getResource() const; // Get the resource of the tile
    int getId() const; // Get the id of the tile
    vector<size_t> getNodes() ; // Get the nodes of the tile
};

#endif // TILE_HPP
