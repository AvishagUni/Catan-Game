#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <unordered_map>
#include <utility>

// Forward declaration
class Vertex;
class Edge;
class Player;

class Hex {
public:
    int x, y;
    std::string resource;
    int hexNumber;
    std::array<Vertex*, 6> vertices;
    std::array<Edge*, 6> edges;

    Hex(int x, int y, const std::string& resource, int hexNumber)
        : x(x), y(y), resource(resource), hexNumber(hexNumber) {
        vertices.fill(nullptr);
        edges.fill(nullptr);
    }
};

class Vertex {
public:
    std::string owner;
    bool hasSettlement;
    bool hasCity;

    Vertex() : owner(""), hasSettlement(false), hasCity(false) {}
};

class Edge {
public:
    std::string owner;
    bool hasRoad;

    Edge() : owner(""), hasRoad(false) {}
};

class Board {
public:
    std::vector<std::vector<Hex>> hexes;
    std::unordered_map<std::string, Vertex*> vertexMap;
    std::unordered_map<std::string, Edge*> edgeMap;
    std::unordered_map<std::string, Player*> players;

    Board();

    bool canPlaceSettlement(int x, int y, int vertexIndex, const std::string& playerName);
    void placeSettlement(int x, int y, int vertexIndex, const std::string& playerName);

    bool canPlaceCity(int x, int y, int vertexIndex, const std::string& playerName);
    void placeCity(int x, int y, int vertexIndex, const std::string& playerName);

    bool canPlaceRoad(int x, int y, int edgeIndex, const std::string& playerName);
    void placeRoad(int x, int y, int edgeIndex, const std::string& playerName);

    void distributeResources(int diceRoll);

private:
    void initializeBoard();
    void initializeVerticesAndEdges();

    std::string vertexKey(int x, int y, int index);
    std::string edgeKey(int x, int y, int index);

    Vertex* getOrCreateVertex(int x, int y, int index);
    Edge* getOrCreateEdge(int x, int y, int index);
};

