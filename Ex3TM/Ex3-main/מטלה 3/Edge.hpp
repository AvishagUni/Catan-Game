// minnesav@gmail.com

#ifndef EDGE_H
#define EDGE_H

class Edge {
public:
    bool hasRoad;
    int owner;  // Player ID
    std::vector<Vertex*> adjacentVertices;
    std::vector<Edge*> adjacentEdges;

    Edge();

    void placeRoad(int playerID);
};

#endif // EDGE_H

