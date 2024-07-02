// minnesav@gmail.com

#ifndef EDGE_H
#define EDGE_H

#include <vector>
#include <string>
#include <iostream>
#include "Vertex.hpp"

namespace Game {

    class Vertex;  // Forward declaration

class Edge {
public:
    bool hasRoad;
    std::string owner;  // Player ID
    int id;
    std::vector<Vertex*> adjacentVertices;
    std::vector<Edge*> adjacentEdges;

    Edge();

    bool operator==(const Edge& other) const {
            // Define the equality comparison for Edge
            return (owner == other.owner &&
                    hasRoad == other.hasRoad &&
                    adjacentVertices == other.adjacentVertices &&
                    adjacentEdges == other.adjacentEdges);
    }
};
}


#endif // EDGE_H

