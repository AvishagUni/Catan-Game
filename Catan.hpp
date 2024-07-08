#ifndef CATAN_HPP
#define CATAN_HPP

#include <vector>
#include "Player.hpp"
#include "Node.hpp"

using namespace std;

class Board;

class Catan {
    vector<Player*> players;
    Board* board;

    public:

    Catan(Player* p1, Player* p2, Player* p3);
    ~Catan();

    void buildRoad(int i, Player* player, bool firstRound = false);   
    void buildSettlement(int i, Player* player, bool firstRound = false);
    void buildCity(int i, Player* player);
    void useDevelopmentCard(Player* player);
    void distributeResources(int diceRoll);
    void checkWinCondition();

    void checkLargestArmy(); 
};

#endif // CATAN_HPP
