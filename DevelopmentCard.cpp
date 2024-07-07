#include <iostream>
#include "DevelopmentCard.hpp"

void DevelopmentCard::use(Player &player, std::vector<Player*> &players) {
    switch (type) {
        case CardType::VictoryPoint:
            player.modifyPoints(1);
            std::cout << player.getName() << " used a Victory Point card and gained 1 victory point!" << std::endl;
            break;
        case CardType::Knight:
            player.modifyKnights(1);
            std::cout << player.getName() << " used a Knight card!" << std::endl;
            break;
        case CardType::RoadBuilding: {
            std::cout << player.getName() << " used a Road Building card!" << std::endl;
            
            int road1, road2;
            std::cout << "Enter the index of the first road you want to build: " << std::endl; 
            std::cin >> road1;
            if (player.canBuyRoad()) {
                player.buyRoad(road1);
            } else {
                std::cout << "Cannot build road at index " << road1 << std::endl;
            }

            std::cout << "Enter the index of the second road you want to build: " << std::endl;
            std::cin >> road2;
            if (player.canBuyRoad()) {
                player.buyRoad(road2);
            } else {
                std::cout << "Cannot build road at index " << road2 << std::endl;
            }
            break;
        }
        case CardType::YearOfPlenty: {
            std::cout << player.getName() << " used a Year of Plenty card!" << std::endl;
            
            int resource1, resource2;
            std::cout << "Enter the index of the first resource you want to take: " << std::endl;
            std::cin >> resource1;
            player.modifyResources(1, static_cast<Resource>(resource1));

            std::cout << "Enter the index of the second resource you want to take: " << std::endl;
            std::cin >> resource2;
            player.modifyResources(1, static_cast<Resource>(resource2));
            break;
        }
        case CardType::Monopoly: {
            std::cout << player.getName() << " used a Monopoly card!" << std::endl;
            
            int resource;
            std::cout << "Enter the index of the resource you want to steal from all players: " << std::endl;
            std::cin >> resource;
            Resource targetResource = static_cast<Resource>(resource);

            for (Player* p : players) {
                if (p != &player) {
                    size_t amount = p->stealResource(targetResource);
                    player.modifyResources(amount, targetResource);
                }
            }
            break;
        }
        default:
            std::cerr << "Unknown card type!" << std::endl;
    }
}





