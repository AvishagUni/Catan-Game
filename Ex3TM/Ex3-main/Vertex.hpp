// minnesav@gmail.com

#ifndef VERTEX_H
#define VERTEX_H

#include <vector> // Include the vector header
#include <string> // Include the string header
#include <iostream> // Include the iostream header

#include "Edge.hpp"

namespace Game {

class Tile;  // Forward declaration
class Edge;  // Forward declaration

class Vertex {
public:
    Vertex();

    bool hasSettlement;
    bool hasCity;
    std::string owner;  // Player ID
    int id;
    std::vector<Vertex*> adjacentVertices;
    std::vector<Edge*> adjacentEdges;
};
    
    }

#endif // VERTEX_H



