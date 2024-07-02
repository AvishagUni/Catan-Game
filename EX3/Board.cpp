#include "Board.hpp"
#include <algorithm>
#include <random>
#include <ctime>
#include "Player.hpp" // Make sure to include Player class

namespace ariel {
    Board::Board() {
        initializeBoard();
        initializeVerticesAndEdges();
    }

    void Board::initializeBoard() {
        // Define the specific layout for a Catan board with hex numbers
        std::vector<std::vector<std::pair<std::string, int>>> layout = {
            {{"", 0}, {"", 0}, {"Wood", 5}, {"Brick", 2}, {"Sheep", 6}, {"", 0}, {"", 0}},
            {{"", 0}, {"Wheat", 3}, {"Sheep", 8}, {"Ore", 10}, {"Wood", 9}, {"Brick", 12}, {"", 0}},
            {{"Wood", 11}, {"Brick", 4}, {"Desert", 0}, {"Sheep", 8}, {"Wheat", 10}, {"Ore", 9}, {"Sheep", 3}},
            {{"", 0}, {"Ore", 6}, {"Wheat", 11}, {"Wood", 4}, {"Brick", 5}, {"Wheat", 2}, {"", 0}},
            {{"", 0}, {"", 0}, {"Sheep", 12}, {"Ore", 3}, {"Wood", 6}, {"", 0}, {"", 0}}
        };

        for (int y = 0; y < layout.size(); ++y) {
            std::vector<Hex> row;
            for (int x = 0; x < layout[y].size(); ++x) {
                if (!layout[y][x].first.empty()) { // Only create Hex objects for non-empty positions
                    std::string resource = layout[y][x].first;
                    int hexNumber = layout[y][x].second;
                    row.emplace_back(x, y, resource, hexNumber);
                } else {
                    row.emplace_back(x, y, "None", 0); // Ensure grid integrity
                }
            }
            hexes.push_back(row);
        }
    }

    void Board::initializeVerticesAndEdges() {
        // Initialize vertices and edges for each hex
        for (auto& row : hexes) {
            for (auto& hex : row) {
                if (hex.resource == "None") continue; // Skip empty hex positions
                for (int i = 0; i < 6; ++i) {
                    hex.vertices[i] = getOrCreateVertex(hex.x, hex.y, i);
                    hex.edges[i] = getOrCreateEdge(hex.x, hex.y, i);
                }
            }
        }
    }

    std::string Board::vertexKey(int x, int y, int index) {
        return std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(index);
    }

    std::string Board::edgeKey(int x, int y, int index) {
        return std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(index);
    }

    Vertex* Board::getOrCreateVertex(int x, int y, int index) {
        std::string key = vertexKey(x, y, index);
        if (vertexMap.find(key) == vertexMap.end()) {
            vertexMap[key] = new Vertex();
        }
        return vertexMap[key];
    }

    Edge* Board::getOrCreateEdge(int x, int y, int index) {
        std::string key = edgeKey(x, y, index);
        if (edgeMap.find(key) == edgeMap.end()) {
            edgeMap[key] = new Edge();
        }
        return edgeMap[key];
    }

    bool Board::canPlaceSettlement(int x, int y, int vertexIndex, const std::string& playerName) {
        Vertex* vertex = getOrCreateVertex(x, y, vertexIndex);
        if (vertex->hasSettlement || vertex->hasCity) {
            return false; // Vertex already has a settlement or city
        }

        // Check for adjacent vertices
        for (int i = 0; i < 6; ++i) {
            int adjX = x, adjY = y, adjVertexIndex = (vertexIndex + i) % 6;
            Vertex* adjVertex = getOrCreateVertex(adjX, adjY, adjVertexIndex);
            if (adjVertex->hasSettlement || adjVertex->hasCity) {
                return false; // Adjacent vertex has a settlement or city
            }
        }

        return true;
    }

    void Board::placeSettlement(int x, int y, int vertexIndex, const std::string& playerName) {
        Vertex* vertex = getOrCreateVertex(x, y, vertexIndex);
        vertex->owner = playerName;
        vertex->hasSettlement = true;
    }

    bool Board::canPlaceCity(int x, int y, int vertexIndex, const std::string& playerName) {
        Vertex* vertex = getOrCreateVertex(x, y, vertexIndex);
        return vertex->hasSettlement && vertex->owner == playerName && !vertex->hasCity;
    }

    void Board::placeCity(int x, int y, int vertexIndex, const std::string& playerName) {
        Vertex* vertex = getOrCreateVertex(x, y, vertexIndex);
        vertex->hasSettlement = false;
        vertex->hasCity = true;
    }

    bool Board::canPlaceRoad(int x, int y, int edgeIndex, const std::string& playerName) {
        Edge* edge = getOrCreateEdge(x, y, edgeIndex);
        if (edge->hasRoad) {
            return false; // Edge already has a road
        }

        // Check if the road connects to a settlement/city of the same player or another road of the same player
        int adjX = x, adjY = y, adjEdgeIndex = (edgeIndex + 3) % 6; // Opposite edge
        Edge* adjEdge = getOrCreateEdge(adjX, adjY, adjEdgeIndex);
        if (adjEdge->owner == playerName && adjEdge->hasRoad) {
            return true;
        }

        for (int i = 0; i < 2; ++i) {
            int vertexIndex = (edgeIndex + i) % 6;
            Vertex* vertex = getOrCreateVertex(x, y, vertexIndex);
            if (vertex->owner == playerName && (vertex->hasSettlement || vertex->hasCity)) {
                return true; // Road connects to player's settlement or city
            }
        }

        return false;
    }

    void Board::placeRoad(int x, int y, int edgeIndex, const std::string& playerName) {
        Edge* edge = getOrCreateEdge(x, y, edgeIndex);
        edge->owner = playerName;
        edge->hasRoad = true;
    }

    void Board::distributeResources(int diceRoll) {
        for (auto& row : hexes) {
            for (auto& hex : row) {
                if (hex.resource == "None") continue; // Skip empty hex positions

                // Check if the dice roll matches the hex's number
                if (hex.hexNumber == diceRoll) {
                    for (int i = 0; i < 6; ++i) {
                        Vertex* vertex = hex.vertices[i];
                        if (vertex && (vertex->hasSettlement || vertex->hasCity)) {
                            int amount = vertex->hasCity ? 2 : 1; // City produces double resources
                            Player* owner = findPlayerByName(vertex->owner);
                            if (owner) {
                                owner->resources[hex.resource] += amount;
                            }
                        }
                    }
                }
            }
        }
    }

    Player* Board::findPlayerByName(const std::string& playerName) {
        auto it = players.find(playerName);
        if (it != players.end()) {
            return it->second;
        }
        return nullptr;
    }
}
