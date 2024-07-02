#include <iostream>
#include <vector>
#include "Catan.hpp"
#include "Player.hpp"
#include "HexTile.hpp"
#include "DevelopmentCard.hpp"

using namespace std;

int main() {
    // Initialize players
    vector<Player*> players;
    initializePlayers(players); // Always initialize 3 players

    // Initialize board
    vector<Tile*> island;
    buildIsland(island); // Always build a 5x5 island

    // Render the initial island
    renderIsland(island); // Assuming a 5x5 board size

    // Main game loop
    int currentPlayer = 0;
    while (true) {
        // Print the current player's turn
        cout << players[currentPlayer]->getName() << "'s turn." << endl;

        // Roll dice and distribute resources
        diceRoll(players, island);

        // Player's turn to take actions
        currentPlayer = takeTurn(players, island, currentPlayer); // Assuming a 5x5 board size

        // Check for win condition
        if (players[currentPlayer]->getVictoryPoints() >= 10) {
            cout << players[currentPlayer]->getName() << " wins the game!" << endl;
            break;
        }
    }

    // Clean up
    for (Player* player : players) {
        delete player;
    }
    for (Tile* tile : island) {
        delete tile;
    }

    return 0;
}


