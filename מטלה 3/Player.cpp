// minnesav@gmail.com

#include "Player.hpp"

namespace Game {
    Player::Player() : victoryPoints(0), playerID(-1), longestRoadLength(0), knightsPlayed(0), board(nullptr) {
        resources = {
                {Resource::WOOD, 0},
                {Resource::BRICK, 0},
                {Resource::WOOL, 0},
                {Resource::OATS, 0},
                {Resource::IRON, 0}
        };
    }

    bool Player::canBuildSettlement(Vertex* vertex) const {
        if (vertex->hasSettlement || vertex->hasCity) {
            return false;  // Cannot build on an occupied vertex
        }
        // Ensure no adjacent vertices have settlements or cities
        for (Vertex* adjacent : vertex->adjacentVertices) {
            if (adjacent->hasSettlement || adjacent->hasCity) {
                return false;  // Cannot build adjacent to another settlement or city
            }
        }
        // Ensure the vertex is connected to one of the player's roads
        for (Edge* edge : vertex->adjacentEdges) {
            if (edge->hasRoad && edge->owner == this->playerID) {
                return true;  // Valid position
            }
        }
        return false;
    }

    bool Player::canBuildRoad(Edge* edge) const {
        if (edge->hasRoad) {
            return false;  // Cannot build on an occupied edge
        }
        // Ensure the road is connected to one of the player's settlements, cities, or roads
        for (Vertex* vertex : edge->adjacentVertices) {
            if ((vertex->hasSettlement || vertex->hasCity) && vertex->owner == this->playerID) {
                return true;  // Valid position
            }
        }
        for (Edge* adjacentEdge : edge->adjacentEdges) {
            if (adjacentEdge->hasRoad && adjacentEdge->owner == this->playerID) {
                return true;  // Valid position
            }
        }
        return false;
    }

    bool Player::canBuildCity(Vertex* vertex) const {
        return vertex->hasSettlement && vertex->owner == this->playerID;  // Can only upgrade own settlements
    }

    void Player::buildSettlement(Vertex* vertex) {
        if (canBuildSettlement(vertex) && resources[Resource::WOOD] >= 1 && resources[Resource::BRICK] >= 1 && resources[Resource::WOOL] >= 1 && resources[Resource::OATS] >= 1) {
            resources[Resource::WOOD]--;
            resources[Resource::BRICK]--;
            resources[Resource::WOOL]--;
            resources[Resource::OATS]--;
            vertex->placeSettlement(this->playerID);
            settlements.push_back(vertex);
            victoryPoints++;
        } else {
            std::cout << "Cannot build settlement here or not enough resources." << std::endl;
        }
    }

    void Player::buildRoad(Edge* edge) {
        if (canBuildRoad(edge) && resources[Resource::WOOD] >= 1 && resources[Resource::BRICK] >= 1) {
            resources[Resource::WOOD]--;
            resources[Resource::BRICK]--;
            edge->placeRoad(this->playerID);
            roads.push_back(edge);

            // Check for longest road
            int longestRoad = calculateLongestRoad();
            if (longestRoad > longestRoadLength) {
                longestRoadLength = longestRoad;
            }
        } else {
            std::cout << "Cannot build road here or not enough resources." << std::endl;
        }
    }

    void Player::buildCity(Vertex* vertex) {
        if (canBuildCity(vertex) && resources[Resource::IRON] >= 3 && resources[Resource::OATS] >= 2) {
            resources[Resource::IRON] -= 3;
            resources[Resource::OATS] -= 2;
            vertex->placeCity(this->playerID);
            cities.push_back(vertex);
            settlements.erase(std::remove(settlements.begin(), settlements.end(), vertex), settlements.end());
            victoryPoints++;  // Gain one additional point (city worth 2, settlement worth 1)
        } else {
            std::cout << "Cannot build city here or not enough resources." << std::endl;
        }
    }

    void Player::addInitialSettlementsAndRoads(std::vector<Vertex*> initialSettlements, std::vector<Edge*> initialRoads) {
        for (auto& vertex : initialSettlements) {
            vertex->placeSettlement(this->playerID);
            settlements.push_back(vertex);
        }
        for (auto& edge : initialRoads) {
            edge->placeRoad(this->playerID);
            roads.push_back(edge);
        }
        victoryPoints = 2;
    }

    bool Player::trade(Player& otherPlayer, Resource give, int giveAmount, Resource receive, int receiveAmount) {
        if (resources[give] >= giveAmount && otherPlayer.resources[receive] >= receiveAmount) {
            resources[give] -= giveAmount;
            resources[receive] += receiveAmount;
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
        if (index >= 0 && index < developmentCards.size()) {
            DevelopmentCard* card = developmentCards[index];
            card->use(*this);
            developmentCards.erase(developmentCards.begin() + index);
            delete card; // Ensure we delete the dynamically allocated card
        } else {
            std::cout << "Invalid development card index." << std::endl;
        }
    }

    void Player::playKnight() {
        knightsPlayed++;
    }

    void Player::displayResources() const {
        std::cout << "Resources: " << std::endl;
        for (const auto& resource : resources) {
            std::cout << " - " << static_cast<int>(resource.first) << ": " << resource.second << std::endl;
        }
    }

    int Player::calculateLongestRoad() const {
        // Implement a BFS/DFS to calculate the longest road
        // This is a simplified version and may need to be adapted to fit the actual game rules

        std::vector<bool> visited(edges.size(), false);
        int longest = 0;

        for (const Edge* road : roads) {
            std::queue<const Edge*> queue;
            queue.push(road);
            int length = 0;

            while (!queue.empty()) {
                const Edge* current = queue.front();
                queue.pop();

                if (visited[current - &edges[0]]) continue;
                visited[current - &edges[0]] = true;
                length++;

                for (const Edge* adj : current->adjacentEdges) {
                    if (adj->owner == this->playerID && !visited[adj - &edges[0]]) {
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

    void Player::executeAction(PlayerAction* action) {
        action->execute(*this, *board);
    }
}




