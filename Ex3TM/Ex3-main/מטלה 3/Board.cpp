// minnesav@gmail.com

#include "Board.hpp"
#include "Dice.hpp"
#include "Tile.hpp"

Board::Board() : longestRoadPlayer(nullptr), largestArmyPlayer(nullptr) {
    initializeBoard();
    initializePlayers();
}
void Board::initializeBoard() {
    std::vector<std::pair<int, char>> tileDefinitions = {
            {2, 'F'}, {3, 'H'}, {3, 'P'}, {4, 'T'}, {4, 'M'}, {5, 'F'},
            {5, 'T'}, {6, 'H'}, {6, 'P'}, {7, 'F'}, {8, 'M'}, {8, 'F'},
            {9, 'H'}, {9, 'P'}, {10, 'T'}, {10, 'M'}, {11, 'P'}, {11, 'D'},
            {12, 'T'}
    };

    // Pre-allocate vertices and edges for the hexagonal grid
    vertices.resize(54);  // 19 tiles * 6 vertices / 2 (shared vertices)
    edges.resize(72);     // 19 tiles * 6 edges / 2 (shared edges)

    // Mapping of tiles to vertices and edges in a hexagonal grid
    // The vertices and edges arrays need to be correctly mapped for a hexagonal grid
    int tileIndex = 0;
    int vertexIndex = 0;
    int edgeIndex = 0;

    for (const auto& tileDef : tileDefinitions) {
        int number = tileDef.first;
        char type = tileDef.second;
        Tile* tile = nullptr;

        switch (type) {
            case 'F':
                tile = new ForestTile(number);
                break;
            case 'H':
                tile = new HillsTile(number);
                break;
            case 'P':
                tile = new PastureTile(number);
                break;
            case 'M':
                tile = new MountainsTile(number);
                break;
            case 'T':
                tile = new FieldsTile(number);
                break;
            case 'D':
                tile = new DesertTile(number);
                break;
            default:
                break;
        }

        // Assign vertices and edges to the tile
        for (int j = 0; j < 6; ++j) {
            tile->vertices[j] = &vertices[vertexIndex++];
            tile->edges[j] = &edges[edgeIndex++];
        }
        tiles.push_back(tile);
    }

    // Initialize adjacency lists
    for (size_t i = 0; i < vertices.size(); ++i) {
        vertices[i].adjacentVertices = getAdjacentVertices(i);
        vertices[i].adjacentEdges = getAdjacentEdges(i);
    }
    for (size_t i = 0; i < edges.size(); ++i) {
        edges[i].adjacentVertices = getAdjacentVerticesForEdge(i);
        edges[i].adjacentEdges = getAdjacentEdgesForEdge(i);
    }
}

void Board::initializePlayers() {
    for (Player& player : players) {
        std::vector<Vertex*> initialSettlements = { &vertices[0], &vertices[1] };  // initial vertices
        std::vector<Edge*> initialRoads = { &edges[0], &edges[1] };  // Example initial edges
        player.addInitialSettlementsAndRoads(initialSettlements, initialRoads);
    }
}

void Board::rollDice() {
    Dice dice;
    int rollResult = dice.roll();
    std::cout << "Dice roll result: " << rollResult << std::endl;

    if (rollResult == 7) {
        handleRobber();
    } else {
        distributeResources(rollResult);
    }
}

void Board::distributeResources(int rollResult) {
    for (const Tile* tile : tiles) {
        if (tile->number == rollResult) {
            Resource resource = tile->getResource();
            if (resource != Resource::NONE) {
                for (Player& player : players) {
                    for (const auto& vertex : player.settlements) {
                        if (std::find(tile->vertices.begin(), tile->vertices.end(), vertex) != tile->vertices.end()) {
                            player.resources[resource]++;
                        }
                    }
                    for (const auto& vertex : player.cities) {
                        if (std::find(tile->vertices.begin(), tile->vertices.end(), vertex) != tile->vertices.end()) {
                            player.resources[resource] += 2;
                        }
                    }
                }
            }
        }
    }
}

void Board::handleRobber() {
    std::cout << "Robber activated! Players with more than 7 resource cards must discard half of them." << std::endl;

    for (Player& player : players) {
        int totalResources = 0;
        for (const auto& resource : player.resources) {
            totalResources += resource.second;
        }

        if (totalResources > 7) {
            std::cout << "Player " << player.playerID + 1 << " must discard " << totalResources / 2 << " cards." << std::endl;
            // Simple discard logic: just zero out resources (could be more sophisticated)
            for (auto& resource : player.resources) {
                resource.second /= 2;
            }
        }
    }

    // In the full game, the player who rolled the 7 would move the robber and steal a resource.
    // This is simplified.
    std::cout << "The player who rolled the 7 should move the robber and can steal a resource from a player adjacent to the new robber location." << std::endl;
}

void Board::checkLongestRoad() {
    Player* currentLongest = longestRoadPlayer;
    int longest = (currentLongest != nullptr) ? currentLongest->longestRoadLength : 0;

    for (Player& player : players) {
        int playerLongestRoad = player.calculateLongestRoad();
        if (playerLongestRoad > longest) {
            if (currentLongest != nullptr) {
                currentLongest->victoryPoints -= 2;  // Remove Longest Road card points from previous holder
            }
            player.victoryPoints += 2;  // Award Longest Road card points to new holder
            longestRoadPlayer = &player;
            longest = playerLongestRoad;
            std::cout << "Player " << player.playerID + 1 << " now has the Longest Road with " << playerLongestRoad << " segments." << std::endl;
        }
    }
}

void Board::checkLargestArmy() {
    Player* currentLargest = largestArmyPlayer;
    int largest = (currentLargest != nullptr) ? currentLargest->knightsPlayed : 0;

    for (Player& player : players) {
        if (player.knightsPlayed > largest && player.knightsPlayed >= 3) {
            if (currentLargest != nullptr) {
                currentLargest->victoryPoints -= 2;  // Remove Largest Army card points from previous holder
            }
            player.victoryPoints += 2;  // Award Largest Army card points to new holder
            largestArmyPlayer = &player;
            largest = player.knightsPlayed;
            std::cout << "Player " << player.playerID + 1 << " now has the Largest Army with " << player.knightsPlayed << " knights
