// minnesav@gmail.com

#include "Player.hpp"

using namespace std;
using namespace Game;

// Constructor with name parameter
Player::Player(const std::string& playerName) 
    : name(playerName), victoryPoints(0), longestRoadLength(0), knightsPlayed(0), board(board) { 
    resources = {
        {Resource::WOOD, 0},
        {Resource::BRICK, 0},
        {Resource::WOOL, 0},
        {Resource::OATS, 0},
        {Resource::IRON, 0}
    };
    std::cout << "Player " << name << " created." << std::endl;
}

void Player::placeInitialSettlementsAndRoads() {
    int vertexIndex;
    int edgeIndex;

    // Ask the player for their initial settlement placement
    for (int i = 0; i < 2; ++i) {
        bool placed = false;
        while (!placed) {
            std::cout << "Player " << name << ", enter the index of the vertex for settlement " << (i + 1) << ": ";
            std::cin >> vertexIndex;

            if (vertexIndex < 0 || static_cast<size_t>(vertexIndex) >= board->vertices.size()) {
                std::cout << "Invalid index. Please enter a valid vertex index.\n";
                continue;
            }

            Vertex* vertex = &board->vertices[vertexIndex];
            std::cout << "Checking vertex " << vertexIndex << std::endl;

            // Check if the vertex is already occupied
            if (std::any_of(settlements.begin(), settlements.end(), [vertexIndex](Vertex* v) { return -1; }) ||
                std::any_of(cities.begin(), cities.end(), [vertexIndex](Vertex* v) { return -1; })) {
                std::cout << "Invalid placement. Please choose another vertex.\n";
                continue;
            }

            // Check if the vertex is adjacent to an existing settlement
            bool adjacentToSettlement = false;
            for (Vertex* adjVertex : vertex->adjacentVertices) {
                if (std::any_of(settlements.begin(), settlements.end(), [adjVertex](Vertex* v) { return v == adjVertex; })) {
                    adjacentToSettlement = true;
                    break;
                }
            }
            if (adjacentToSettlement) {
                std::cout << "Invalid placement. The vertex is adjacent to an existing settlement. Please choose another vertex.\n";
                continue;
            }

            // Place settlement
            settlements.push_back(vertex);
            std::cout << "Settlement built successfully at vertex " << vertexIndex << ".\n";
            placed = true;
        }
    }

    // Ask the player for their initial road placement
    for (int i = 0; i < 2; ++i) {
        bool placed = false;
        while (!placed) {
            std::cout << "Player " << name << ", enter the index of the edge for road " << (i + 1) << ": ";
            std::cin >> edgeIndex;

            if (edgeIndex < 0 || static_cast<size_t>(edgeIndex) >= board->edges.size()) {
                std::cout << "Invalid index. Please enter a valid edge index.\n";
                continue;
            }

            Edge* edge = &board->edges[edgeIndex];
            std::cout << "Checking edge " << edgeIndex << std::endl;
    

            // Check if the edge is already occupied
            if (std::any_of(roads.begin(), roads.end(), [edgeIndex](Edge* e) { return -2; })) {
                std::cout << "Invalid placement. Please choose another edge.\n";
                continue;
            }

            // Place road
            roads.push_back(edge);
            std::cout << "Road built successfully at edge " << edgeIndex << ".\n";
            placed = true;
        }
    }
}


void Player::rollDice() {
    Dice dice;
    int rollResult = dice.roll();
    std::cout << "Dice roll result: " << rollResult << std::endl;
    board->distributeResources(rollResult);
    }

void Player::buyDevelopmentCard() {
    const int woolCost = 1;
    const int oatsCost = 1;
    const int ironCost = 1;

    // Check if the player has enough resources
    if (resources[Resource::WOOL] < woolCost || 
        resources[Resource::OATS] < oatsCost || 
        resources[Resource::IRON] < ironCost) {
        std::cout << "Not enough resources to buy a development card." << std::endl;
        return;
    }

    // Deduct resources
    resources[Resource::WOOL] -= woolCost;
    resources[Resource::OATS] -= oatsCost;
    resources[Resource::IRON] -= ironCost;

    // Randomly select a development card
    DevelopmentCard* newCard = nullptr;
    int cardType = rand() % 5; // Assuming 4 types of cards

    switch (cardType) {
        case 0:
            newCard = new KnightCard();
            std::cout << "You received a Knight card." << std::endl;
            break;
        case 1:
            newCard = new MonopolyCard();
            std::cout << "You received a Monopoly card." << std::endl;

            break;
        case 2:
            newCard = new RoadBuildingCard();
            std::cout << "You received a Road Building card." << std::endl;
            break;
        case 3:
            newCard = new YearOfPlentyCard();
            std::cout << "You received a Year of Plenty card." << std::endl;
            break;
        case 4:
            newCard = new VictoryPointCard();
            std::cout << "You received a Victory Point card." << std::endl;
            victoryPoints++;
            break;
    }

    // Add the card to the player's collection
    developmentCards.push_back(newCard);
}

bool Player::placeSettlement(Vertex* vertex) {
    const int woodCost = 1;
    const int brickCost = 1;
    const int woolCost = 1;
    const int oatsCost = 1;

    // Check if the player has enough resources
    if (resources[Resource::WOOD] < woodCost || 
        resources[Resource::BRICK] < brickCost || 
        resources[Resource::WOOL] < woolCost || 
        resources[Resource::OATS] < oatsCost) {
        std::cout << "Not enough resources to build a settlement." << std::endl;
        return false;
    }

    // Check if the vertex is already occupied
    if (std::any_of(settlements.begin(), settlements.end(), [vertex](Vertex* v) { return v == vertex; }) ||
        std::any_of(cities.begin(), cities.end(), [vertex](Vertex* v) { return v == vertex; })) {
        return false;
    }

    // Check if the vertex is adjacent to one of the player's roads
    if (!settlements.empty()) {
        for (auto* road : roads) {
            if (std::find(road->adjacentVertices.begin(), road->adjacentVertices.end(), vertex) != road->adjacentVertices.end()) {
                // Deduct resources
                resources[Resource::WOOD] -= woodCost;
                resources[Resource::BRICK] -= brickCost;
                resources[Resource::WOOL] -= woolCost;
                resources[Resource::OATS] -= oatsCost;

                settlements.push_back(vertex);
                std::cout << "Settlement built successfully." << std::endl;
                return true;
            }
        }
        return false;
    }

    // For initial placement, we may want to allow placement without adjacent roads
    if (settlements.empty()) {
        // Deduct resources
        resources[Resource::WOOD] -= woodCost;
        resources[Resource::BRICK] -= brickCost;
        resources[Resource::WOOL] -= woolCost;
        resources[Resource::OATS] -= oatsCost;

        settlements.push_back(vertex);
        std::cout << "Settlement built successfully." << std::endl;
        return true;
    }

    return false;
}

bool Player::placeRoad(Edge* edge) {
    const int woodCost = 1;
    const int brickCost = 1;

    // Check if the player has enough resources
    if (resources[Resource::WOOD] < woodCost || resources[Resource::BRICK] < brickCost) {
        std::cout << "Not enough resources to build a road." << std::endl;
        return false;
    }

    // Check if the edge is already occupied
    if (std::any_of(roads.begin(), roads.end(), [edge](Edge* e) { return e == edge; })) {
        return false;
    }

    // Check if the edge is adjacent to one of the player's settlements or roads
    for (auto* settlement : settlements) {
        if (std::find(edge->adjacentVertices.begin(), edge->adjacentVertices.end(), settlement) != edge->adjacentVertices.end()) {
            // Deduct resources
            resources[Resource::WOOD] -= woodCost;
            resources[Resource::BRICK] -= brickCost;

            roads.push_back(edge);
            std::cout << "Road built successfully." << std::endl;
            return true;
        }
    }

    for (auto* road : roads) {
        if (std::find(road->adjacentEdges.begin(), road->adjacentEdges.end(), edge) != road->adjacentEdges.end()) {
            // Deduct resources
            resources[Resource::WOOD] -= woodCost;
            resources[Resource::BRICK] -= brickCost;

            roads.push_back(edge);
            std::cout << "Road built successfully." << std::endl;
            return true;
        }
    }

    // For initial placement, we may want to allow placement without adjacent settlements or roads
    if (roads.empty()) {
        // Deduct resources
        resources[Resource::WOOD] -= woodCost;
        resources[Resource::BRICK] -= brickCost;

        roads.push_back(edge);
        std::cout << "Road built successfully." << std::endl;
        return true;
    }

    return false;
}

bool Player::placeCity(Vertex* vertex) {
    const int ironCost = 3;
    const int oatsCost = 2;

    // Check if the player has enough resources
    if (resources[Resource::IRON] < ironCost || resources[Resource::OATS] < oatsCost) {
        std::cout << "Not enough resources to build a city." << std::endl;
        return false;
    }

    // Check if the vertex already has a settlement but not a city
    auto it = std::find(settlements.begin(), settlements.end(), vertex);
    if (it != settlements.end() && std::find(cities.begin(), cities.end(), vertex) == cities.end()) {
        // Deduct resources
        resources[Resource::IRON] -= ironCost;
        resources[Resource::OATS] -= oatsCost;

        settlements.erase(it);
        cities.push_back(vertex);
        std::cout << "City built successfully." << std::endl;
        return true;
    }
    return false;
}

bool Player::trade(Player& otherPlayer, Resource give, int giveAmount, Resource receive, int receiveAmount) {
    if (resources[give] >= giveAmount && otherPlayer.resources[receive] >= receiveAmount) {
        resources[give] -= giveAmount;
        resources[receive] += giveAmount;
        otherPlayer.resources[receive] -= receiveAmount;
        otherPlayer.resources[give] += giveAmount;
        return true;
    }
    return false;
}

void Player::tradeWithBank(Resource give, int giveAmount, Resource receive) {
    int tradeRate = 4; // Default bank trade rate is 4:1
    if (giveAmount >= tradeRate) {
        int numTrades = giveAmount / tradeRate;
        resources[give] -= numTrades * tradeRate;
        resources[receive] += numTrades;
        std::cout << "Traded " << numTrades * tradeRate << " " << static_cast<int>(give) << " for " << numTrades << " " << static_cast<int>(receive) << " with the bank." << std::endl;
    } else {
        std::cout << "Not enough resources to trade with the bank." << std::endl;
    }
}

void Player::useDevelopmentCard(int index) {
    if (index >= 0 && static_cast<size_t>(index) < developmentCards.size()) {
        DevelopmentCard* card = developmentCards[index];
        card->use(*this);
        developmentCards.erase(developmentCards.begin() + index);
        delete card; // Ensure we delete the dynamically allocated card
    } else {
        std::cout << "Invalid development card index." << std::endl;
    }
}

void Player::endTurn() {
    board->checkLongestRoad(); // Check for Longest Road after each turn
    cout << "Ending turn for Player " << this->name<< endl;
}

void Player::displayResources() const {
    std::cout << "Resources: " << std::endl;
    for (const auto& resource : resources) {
        std::cout << " - " << static_cast<int>(resource.first) << ": " << resource.second << std::endl;
    }
}

int Player::calculateLongestRoad() const {
    if (!board) {
        std::cerr << "Board is not set for the player." << std::endl;
        return 0;
    }

    const auto& edges = board->edges; // Get the edges from the board
    std::vector<bool> visited(edges.size(), false);
    int longest = 0;

    for (const Edge* road : roads) {
        std::queue<const Edge*> queue;
        queue.push(road);
        int length = 0;

        while (!queue.empty()) {
            const Edge* current = queue.front();
            queue.pop();

            auto it = std::find(edges.begin(), edges.end(), *current); // Dereference the pointer
            if (it == edges.end()) continue;

            int index = std::distance(edges.begin(), it);
            if (visited[index]) continue;

            visited[index] = true;
            length++;

            for (const Edge* adj : current->adjacentEdges) {
                auto adj_it = std::find(edges.begin(), edges.end(), *adj); // Dereference the pointer
                if (adj_it == edges.end()) continue;

                int adj_index = std::distance(edges.begin(), adj_it);
                if (!visited[adj_index] && adj->owner == this->name) {
                    queue.push(adj);
                }
            }
        }

        if (length > longest) {
            longest = length;
        }
    }

    return longest;
}

void Player::printPoints() const {
    int points = victoryPoints;
    if (longestRoadLength >= 5) {
        points += 2;
    }
    if (knightsPlayed >= 3) {
        points += 2;
    }
    std::cout << "Player " << name << " has " << points << " points." << std::endl;
}

void Player::executeAction(PlayerAction* action) {
    action->execute(*this, *board);
}

