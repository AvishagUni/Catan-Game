// minnesav@gmail.com

#include "DevelopmentCard.hpp"

using namespace std;
using namespace Game;

namespace Game {

std::string resourceToString(Resource resource) {
    switch (resource) {
        case Resource::WOOD: return "WOOD";
        case Resource::BRICK: return "BRICK";
        case Resource::WOOL: return "WOOL";
        case Resource::OATS: return "OATS";
        case Resource::IRON: return "IRON";
        default: return "UNKNOWN";
    }
}

void KnightCard::use(Player& player) {
    player.knightsPlayed++;
}

void MonopolyCard::use(Player& player) {
    std::cout << "Choose a resource to monopolize (0:WOOD, 1:BRICK, 2:WOOL, 3:OATS, 4:IRON): ";
    int resourceIndex;
    std::cin >> resourceIndex;
    if (resourceIndex < 0 || resourceIndex > 4) {
        std::cout << "Invalid resource index." << std::endl;
        return;
    }
    Resource resource = static_cast<Resource>(resourceIndex);
    int totalMonopolized = 0;
    if (player.board) { // Ensure player.board is not null
        for (Player &otherPlayer : player.board->players) {
            if (&otherPlayer != &player) {
                totalMonopolized += otherPlayer.resources[resource];
                otherPlayer.resources[resource] = 0;
            }
        }
        player.resources[resource] += totalMonopolized;
        std::cout << "You monopolized " << totalMonopolized << " " << resourceToString(resource) << " cards." << std::endl;
    } else {
        std::cout << "Player board is not initialized." << std::endl;
    }
}

void RoadBuildingCard::use(Player& player) {
    std::cout << "Build two roads for free." << std::endl;
    if (player.board) { // Ensure player.board is not null
        for (int i = 0; i < 2; ++i) {
            int edgeIndex;
            std::cout << "Enter edge index to build road: ";
            std::cin >> edgeIndex;
            if (edgeIndex >= 0 && edgeIndex < static_cast<int>(player.board->edges.size())) {
                player.placeRoad(&player.board->edges[edgeIndex]);
            } else {
                std::cout << "Invalid edge index." << std::endl;
            }
        }
    } else {
        std::cout << "Player board is not initialized." << std::endl;
    }
}

void YearOfPlentyCard::use(Player& player) {
    std::cout << "Choose two resources from the bank." << std::endl;
    for (int i = 0; i < 2; ++i) {
        int resourceIndex;
        std::cout << "Enter resource (0:WOOD, 1:BRICK, 2:WOOL, 3:OATS, 4:IRON): ";
        std::cin >> resourceIndex;
        if (resourceIndex < 0 || resourceIndex > 4) {
            std::cout << "Invalid resource index." << std::endl;
            return;
        }
        Resource resource = static_cast<Resource>(resourceIndex);
        player.resources[resource]++;
    }
}

void VictoryPointCard::use(Player& player) {
    player.victoryPoints++; }

}  // namespace Game

    





