// minnesav@gmail.com

#include "DevelopmentCard.hpp"

namespace Game {
    namespace DevelopmentCards {
        void KnightCard::use(Player &player) {
            player.playKnight();
        }

        void MonopolyCard::use(Player &player) {
            std::cout << "Choose a resource to monopolize (0:WOOD, 1:BRICK, 2:WOOL, 3:OATS, 4:IRON): ";
            int resourceIndex;
            std::cin >> resourceIndex;
            Resource resource = static_cast<Resource>(resourceIndex);
            int totalMonopolized = 0;
            for (Player &otherPlayer: player.board->players) {
                if (&otherPlayer != &player) {
                    totalMonopolized += otherPlayer.resources[resource];
                    otherPlayer.resources[resource] = 0;
                }
            }
            player.resources[resource] += totalMonopolized;
            std::cout << "You monopolized " << totalMonopolized << " " << resourceIndex << " cards." << std::endl;
        }

        void RoadBuildingCard::use(Player &player) {
            std::cout << "Build two roads for free." << std::endl;
            for (int i = 0; i < 2; ++i) {
                int edgeIndex;
                std::cout << "Enter edge index to build road: ";
                std::cin >> edgeIndex;
                if (edgeIndex >= 0 && edgeIndex < player.board->edges.size()) {
                    player.buildRoad(&player.board->edges[edgeIndex]);
                } else {
                    std::cout << "Invalid edge index." << std::endl;
                }
            }
        }

        void YearOfPlentyCard::use(Player &player) {
            std::cout << "Choose two resources from the bank." << std::endl;
            for (int i = 0; i < 2; ++i) {
                int resourceIndex;
                std::cout << "Enter resource (0:WOOD, 1:BRICK, 2:WOOL, 3:OATS, 4:IRON): ";
                std::cin >> resourceIndex;
                Resource resource = static_cast<Resource>(resourceIndex);
                player.resources[resource]++;
            }
        }
    }
}



