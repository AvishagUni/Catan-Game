// minnesav@gmail.com

#ifndef VERTEX_H
#define VERTEX_H

class Vertex {
public:
    bool hasSettlement;
    bool hasCity;
    int owner;  // Player ID
    std::vector<Vertex*> adjacentVertices;
    std::vector<Edge*> adjacentEdges;

    Vertex();

    void placeSettlement(int playerID);
    void placeCity(int playerID);
};

#endif // VERTEX_H



