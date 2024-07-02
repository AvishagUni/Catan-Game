// minnesav@gmail.com

#include "Board.hpp"
#include "Player.hpp"
#include "DevelopmentCard.hpp"
#include "PlayerAction.hpp"

using namespace Game;

void playerTurn(Player& currentPlayer, Board& board, std::vector<Player>& players) {
    int choice;
    bool turnEnded = false;

    while (!turnEnded) {
        std::cout << "Player " << currentPlayer.playerID + 1 << "'s turn. Choose an action:" << std::endl;
        std::cout << "1. Build Settlement" << std::endl;
        std::cout << "2. Build Road" << std::endl;
        std::cout << "3. Build City" << std::endl;
        std::cout << "4. Trade with Player" << std::endl;
        std::cout << "5. Trade with Bank" << std::endl;
        std::cout << "6. Use Development Card" << std::endl;
        std::cout << "7. End Turn" << std::endl;
        std::cin >> choice;

        PlayerAction* action = nullptr;

        switch (choice) {
            case 1:
                action = new BuildSettlementAction();
                break;
            case 2:
                action = new BuildRoadAction();
                break;
            case 3:
                action = new BuildCityAction();
                break;
            case 4:
                action = new TradeWithPlayerAction();
                break;
            case 5:
                action = new TradeWithBankAction();
                break;
            case 6:
                action = new UseDevelopmentCardAction();
                break;
            case 7:
                action = new EndTurnAction();
                turnEnded = true;
                break;
            default:
                std::cout << "Invalid choice." << std::endl;
                break;
        }

        if (action) {
            currentPlayer.executeAction(action);
            delete action;
        }
    }
}

bool checkWinCondition(const Player& player) {
    return player.victoryPoints >= 10;
}

int main() {
    Board board;
    std::vector<Player> players(3);
    board.players = players;

    for (int i = 0; i < players.size(); ++i) {
        players[i].playerID = i;  // Assign player IDs
        players[i].board = &board; // Set the board pointer for each player
        std::vector<Vertex*> initialSettlements = { &board.vertices[i * 2], &board.vertices[i * 2 + 1] };
        std::vector<Edge*> initialRoads = { &board.edges[i * 2], &board.edges[i * 2 + 1] };
        players[i].addInitialSettlementsAndRoads(initialSettlements, initialRoads);
    }

    bool gameOver = false;
    int turn = 0;

    while (!gameOver) {
        Player& currentPlayer = players[turn % players.size()];
        board.rollDice();
        currentPlayer.displayResources();
        playerTurn(currentPlayer, board, players);

        board.checkLongestRoad();  // Check for Longest Road after each turn
        board.checkLargestArmy();  // Check for Largest Army after each turn

        if (checkWinCondition(currentPlayer)) {
            std::cout << "Player " << currentPlayer.playerID + 1 << " wins!" << std::endl;
            gameOver = true;
        }

        turn++;
    }

    return 0;
}







