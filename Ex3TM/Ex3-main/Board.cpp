// minnesav@gmail.com

#include "Board.hpp"

using namespace std;
using namespace Game;

// Assumes vertices are arranged in rows
vector<Vertex*> Board::getAdjacentVertices(size_t index) {
    vector<Vertex*> adjacentVertices;

    if (index > 0) {
        adjacentVertices.push_back(&vertices[index - 1]);
    }
    if (index < vertices.size() - 1) {
        adjacentVertices.push_back(&vertices[index + 1]);
    }

    // More complex adjacency logic may be required based on the hexagonal layout
    return adjacentVertices;
}

// Assumes edges are arranged in rows
vector<Edge*> Board::getAdjacentEdges(size_t index) {
    vector<Edge*> adjacentEdges;

    // Example logic for adjacency in a hexagonal grid (needs to be adapted to the actual grid structure)
    if (index > 0) {
        adjacentEdges.push_back(&edges[index - 1]);
    }
    if (index < edges.size() - 1) {
        adjacentEdges.push_back(&edges[index + 1]);
    }

    // More complex adjacency logic may be required based on the hexagonal layout
    return adjacentEdges;
}

vector<Vertex*> Board::getAdjacentVerticesForEdge(size_t index) {
    vector<Vertex*> adjacentVertices;

    // Example logic for adjacency in a hexagonal grid (needs to be adapted to the actual grid structure)
    if (index < vertices.size() - 1) {
        adjacentVertices.push_back(&vertices[index]);
        adjacentVertices.push_back(&vertices[index + 1]);
    }

    // More complex adjacency logic may be required based on the hexagonal layout
    return adjacentVertices;
}

vector<Edge*> Board::getAdjacentEdgesForEdge(size_t index) {
    vector<Edge*> adjacentEdges;

    // Example logic for adjacency in a hexagonal grid (needs to be adapted to the actual grid structure)
    if (index < edges.size() - 1) {
        adjacentEdges.push_back(&edges[index]);
        adjacentEdges.push_back(&edges[index + 1]);
    }

    // More complex adjacency logic may be required based on the hexagonal layout
    return adjacentEdges;
}

Board::Board() : longestRoadPlayer(nullptr), largestArmyPlayer(nullptr) { 
    initializeBoard();
    initializePlayers();
}

void Board::initializeBoard() {
    vector<pair<int, char>> tileDefinitions = {
        {2, 'F'}, {3, 'H'}, {3, 'P'}, {4, 'T'}, {4, 'M'}, {5, 'F'},
        {5, 'T'}, {6, 'H'}, {6, 'P'}, {7, 'F'}, {8, 'M'}, {8, 'F'},
        {9, 'H'}, {9, 'P'}, {10, 'T'}, {10, 'M'}, {11, 'P'}, {11, 'D'},
        {12, 'T'}
    };

    vertices.resize(54);  // 19 tiles * 6 vertices / 2 (shared vertices)
    edges.resize(72);     // 19 tiles * 6 edges / 2 (shared edges)

    // Initialize vertices
    for (size_t i = 0; i < vertices.size(); ++i) {
        vertices[i].id = i;
    }

    // Initialize edges
    for (size_t i = 0; i < edges.size(); ++i) {
        edges[i].id = i;
    }

    int tileIndex = 0;

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
                throw runtime_error("Invalid tile type");
        }

        // Assign vertices and edges to the tile
        for (int j = 0; j < 6; ++j) {
            tile->vertices[j] = &vertices[(tileIndex * 6 + j) % vertices.size()]; 
            tile->edges[j] = &edges[(tileIndex * 6 + j) % edges.size()];
        }
        tiles.push_back(tile);
        tileIndex++;
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

    cout << "Board initialized with " << vertices.size() << " vertices and " << edges.size() << " edges." << endl;
}

void Board::initializePlayers() {
    for (Player& player : players) {
        int vertexIndex;
        int edgeIndex;

        // Ask the player for their initial settlement placement
        for (int i = 0; i < 2; ++i) {
            bool placed = false;
            while (!placed) {
                cout << "Player " << player.name << ", enter the index of the vertex for settlement " << (i + 1) << ": ";
                cin >> vertexIndex;

                if (vertexIndex < 0 || vertexIndex >= vertices.size()) {
                    cout << "Invalid index. Please enter a valid vertex index.\n";
                    continue;
                }

                placed = player.placeSettlement(&vertices[vertexIndex]);
                if (!placed) {
                    cout << "Invalid placement. Please choose another vertex.\n"; }
                else {
                    cout << "Player " << player.name << " placed a settlement on vertex " << vertexIndex << endl;
                    }
                }
            }
        

        // Ask the player for their initial road placement
        for (int i = 0; i < 2; ++i) {
            bool placed = false;
            while (!placed) {
                cout << "Player " << player.name<< ", enter the index of the edge for road " << (i + 1) << ": ";
                cin >> edgeIndex;

                if (edgeIndex < 0 || edgeIndex >= edges.size()) {
                    cout << "Invalid index. Please enter a valid edge index.\n";
                    continue;
                }

                placed = player.placeRoad(&edges[edgeIndex]);
                if (!placed) {
                    cout << "Invalid placement. Please choose another edge.\n";
                }
            }
        }
    }
}


void Board::distributeResources(int rollResult) {
    for (const Tile* tile : tiles) {
        if (tile->number == rollResult) {
            Resource resource = tile->getResource();
            if (resource != Resource::NONE) {
                for (Player& player : players) {
                    for (const auto& vertex : player.settlements) {
                        if (std::find(std::begin(tile->vertices), std::end(tile->vertices), vertex) != std::end(tile->vertices)) {
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

void Board::checkLongestRoad() {
    Game::Player* currentLongest = longestRoadPlayer;
    int longest = (currentLongest != nullptr) ? currentLongest->longestRoadLength : 0;

    for (Game::Player& player : players) {
        int playerLongestRoad = player.calculateLongestRoad();
        if (playerLongestRoad > longest) {
            if (currentLongest != nullptr) {
                currentLongest->victoryPoints -= 2;  // Remove Longest Road card points from previous holder
            }
            player.victoryPoints += 2;  // Award Longest Road card points to new holder
            longestRoadPlayer = &player;
            longest = playerLongestRoad;
            std::cout << "Player " << player.name << " now has the Longest Road with " << playerLongestRoad << " segments." << std::endl;
        }
    }
}

void Board::checkLargestArmy() {
    Game::Player* currentLargest = largestArmyPlayer;
    int largest = (currentLargest != nullptr) ? currentLargest->knightsPlayed : 0;

    for (Game::Player& player : players) {
        if (player.knightsPlayed > largest && player.knightsPlayed >= 3) {
            if (currentLargest != nullptr) {
                currentLargest->victoryPoints -= 2;  // Remove Largest Army card points from previous holder
            }
            player.victoryPoints += 2;  // Award Largest Army card points to new holder
            largestArmyPlayer = &player;
            largest = player.knightsPlayed;
            std::cout << "Player " << player.name << " now has the Largest Army with " << player.knightsPlayed << " knights played." << std::endl;
        }
    }
}

void Board::printWinner() {
    Player* winner = nullptr;
    for (Player& player : players) {
        if (player.victoryPoints >= 10) {
            winner = &player;
            break;
        }
    }
    if (winner != nullptr) {
        std::cout << "Player " << winner->name<< " wins!" << std::endl;
    } else {
        std::cout << "No winner yet." << std::endl;
    }

}


