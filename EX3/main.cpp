#include <iostream>
#include "player.cpp"

int main() {
    Board board;
    Player player1("Alice");
    Player player2("Bob");

    board.addPlayer(&player1);
    board.addPlayer(&player2);

    // Example: add resources to players
    player1.resources["Wood"] = 2;
    player1.resources["Brick"] = 2;
    player1.resources["Sheep"] = 1;
    player1.resources["Wheat"] = 3;
    player1.resources["Ore"] = 3;

    player2.resources["Wood"] = 2;
    player2.resources["Brick"] = 2;

    // Example usage: player 1 tries to place a settlement
    if (player1.placeSettlement(board, 2, 2, 0)) {
        std::cout << "Alice placed a settlement successfully!" << std::endl;
    } else {
        std::cout << "Alice failed to place a settlement." << std::endl;
    }

    // Example usage: player 1 tries to place a city
    if (player1.placeCity(board, 2, 2, 0)) {
        std::cout << "Alice placed a city successfully!" << std::endl;
    } else {
        std::cout << "Alice failed to place a city." << std::endl;
    }

    // Example usage: player 1 tries to place a road
    if (player1.placeRoad(board, 2, 2, 0)) {
        std::cout << "Alice placed a road successfully!" << std::endl;
    } else {
        std::cout << "Alice failed to place a road." << std::endl;
    }

    // Example usage: player 2 tries to place a road
    if (player2.placeRoad(board, 2, 2, 1)) {
        std::cout << "Bob placed a road successfully!" << std::endl;
    } else {
        std::cout << "Bob failed to place a road." << std::endl;
    }

    // Example usage: rolling dice and distributing resources
    int diceRoll = player1.rollDice();
    std::cout << "Dice roll: " << diceRoll << std::endl;
    board.distributeResources(diceRoll);

    // Print resources after distribution
    std::cout << "Alice's resources: ";
    for (const auto& resource : player1.resources) {
        std::cout << resource.first << ": " << resource.second << " ";
    }
    std::cout << std::endl;

    std::cout << "Bob's resources: ";
    for (const auto& resource : player2.resources) {
        std::cout << resource.first << ": " << resource.second << " ";
    }
    std::cout << std::endl;

    return 0;
}



