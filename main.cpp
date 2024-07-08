#include "Catan.hpp"
#include "Tile.hpp"

using namespace std;

int main()
{
    Player* player1 = new Player("Avishag");
    Player* player2 = new Player("Yael");
    Player* player3 = new Player("Shir");

    Catan catan(player1, player2, player3);

    catan.buildSettlement(5, player1, true);
    catan.buildRoad(5, player1, true);
    catan.buildSettlement(27, player1, true);
    catan.buildRoad(29, player1, true);

    catan.buildSettlement(20, player2, true);
    catan.buildRoad(22, player2, true);
    catan.buildSettlement(41, player2, true);
    catan.buildRoad(65, player2, true);

    catan.buildSettlement(19, player3, true);
    catan.buildRoad(21, player3, true);
    catan.buildSettlement(33, player3, true);
    catan.buildRoad(35, player3, true);

    // Player 1's turn
    catan.distributeResources(6);
    player1->tradeWithPlayer(player2, {1, 0, 0, 0, 0}, {0, 1, 0, 0, 0}); // trade one brick with one grain


    // Player 2's turn
    catan.distributeResources(3);
    catan.buildRoad(43, player2, false);


    // Player 3's turn
    catan.distributeResources(5);
    player3->tradeWithPlayer(player1, {1, 0, 0, 0, 0}, {0, 1, 0, 0, 0}); // trade one brick for one grain
    player3->tradeWithPlayer(player2, {0, 0, 1, 0, 0}, {0, 0, 0, 1, 0}); // trade one lumber for one ore
    player3->buyDevelopmentCard();


    // Player 1's turn
    catan.distributeResources(12);
    try {
        catan.buildCity(4, player1);
    } catch (const invalid_argument &e) { // not enough resources
        cout << e.what() << endl;
    }

    // Player 2's turn
    catan.distributeResources(4);
    player2->tradeWithPlayer(player1, {0, 1, 0, 0, 0}, {1, 1, 0, 0, 0}); // trade one grain for grain and brick
    player2->buySettlement(32);
    cout << "City bought successfully!" << endl;

    // Player 3's turn
    catan.distributeResources(11);
    try {
        player3->tradeWithBank(Resource::LUMBER, Resource::ORE);
    } catch (const invalid_argument &e) {
        cout << e.what() << endl;
    }
    catan.useDevelopmentCard(player3);

    // End of game
    catan.checkLargestArmy();
    catan.checkWinCondition();

    return 0;



}