#ifndef CATAN_HPP
#define CATAN_HPP

#include "Player.hpp"
#include "Board.hpp"
#include <vector>
#include <map>

namespace ariel
{
    class Catan
    {
    private:
        Player &player1;
        Player &player2;
        Player &player3;
        Board board;
        Player *currentPlayer;
        Player *longestRoadPlayer;
        Player *largestArmyPlayer;
        int longestRoadLength;
        int largestArmySize;
        int turn;
        std::vector<Player *> players;

    public:
    
        Catan(Player &p1, Player &p2, Player &p3);

        void ChooseStartingPlayer();

        Board &getBoard();

        void nextTurn();

        Player *getCurrentPlayer();

        void printWinner();

        void distributeResources(int roll);

        void setupGame();

        void updateLongestRoad(Player &player, int roadLength);

        void updateLargestArmy(Player &player, int armySize);

        const std::vector<Player *> &getPlayers() const;

        int getTurn() const; // Declare getTurn function

        
    };
}

#endif







