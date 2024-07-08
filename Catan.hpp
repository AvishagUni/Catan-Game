// minnesav@gmail.com

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

    Catan(Player* p1, Player* p2, Player* p3); // Constructor
    ~Catan(); // Destructor

    Board* getBoard(); // Get the board

    void buildRoad(int i, Player* player, bool firstRound = false); // Build a road   
    void buildSettlement(int i, Player* player, bool firstRound = false); // Build a settlement
    void buildCity(int i, Player* player); // Build a city
    void useDevelopmentCard(Player* player); // Use a development card
    void distributeResources(int diceRoll); // Distribute resources
    void checkWinCondition(); // Check if a player has won

    void checkLargestArmy();  // Check if a player has the largest army (3 knights)
};

#endif // CATAN_HPP
