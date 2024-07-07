#include <vector>
#include "Player.hpp"
#include "Board.hpp"
#include "Node.hpp"

using namespace std;

class Catan {
    vector<Player*> players;
    Board board;

    public:

    Catan(Player* p1, Player* p2, Player* p3);
    ~Catan();

    void buildRoad(int i, Player* player);   
    void buildSettlement(int i, Player* player);
    void buildCity(int i, Player* player);
    void useDevelopmentCard(Player* player);
    void distributeResources(int diceRoll);
    void checkWinCondition();

    void checkLargestArmy(); 
    void checkLongestRoad();
};