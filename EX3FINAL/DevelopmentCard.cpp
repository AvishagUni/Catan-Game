#include "Catan.hpp"
#include <iostream>

void Card::use(Player& player, std::vector<Tile*>& island, std::vector<Player*>& players) {
    switch (type) {
        case CardType::VictoryPoint:
            player.modifyVictoryPoints(1);
            std::cout << player.getName() << " used a Victory Point card and gained 1 victory point!" << std::endl;
            break;
        case CardType::Knight:
            player.modifyKnights(1);
            std::cout << player.getName() << " used a Knight card!" << std::endl;
            break;
        case CardType::RoadBuilding:
            std::cout << player.getName() << " used a Road Building card!" << std::endl;
            // Implement logic to build two roads
            buildTwoRoads(player, island);
            break;
        case CardType::YearOfPlenty:
            std::cout << player.getName() << " used a Year of Plenty card!" << std::endl;
            // Implement logic to take two resource cards from the bank
            takeTwoResources(player);
            break;
        case CardType::Monopoly:
            std::cout << player.getName() << " used a Monopoly card!" << std::endl;
            // Implement logic to take all resources of one type from other players
            takeAllResourcesOfOneType(player, players);
            break;
    }
}





