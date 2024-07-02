// minnesav@gmail.com

/**
 * Demo file for Ex3.
 *
 */
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Board.hpp"
#include "Player.hpp"
#include "Dice.hpp"
#include "DevelopmentCard.hpp"
#include "PlayerAction.hpp"

using namespace std;
using namespace Game;

int main()
{
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");

    // Initialize board
    Board board;
    
    // Starting of the game. Every player places two settlements and two roads.
    // Assume it starts with p1 (Player 1)
    vector<Vertex*> vertices1 = {&board.vertices[5], &board.vertices[6]};
    vector<Edge*> edges1 = {&board.edges[5], &board.edges[6]};
    p1.placeInitialSettlementsAndRoads();

    vector<Vertex*> vertices2 = {&board.vertices[3], &board.vertices[4]};
    vector<Edge*> edges2 = {&board.edges[3], &board.edges[4]};
    p2.placeInitialSettlementsAndRoads();

    vector<Vertex*> vertices3 = {&board.vertices[8], &board.vertices[9]};
    vector<Edge*> edges3 = {&board.edges[8], &board.edges[9]};
    p3.placeInitialSettlementsAndRoads();

    // Simulate turns
    p1.rollDice();                                    // Let's say it prints 4. Then, p2 gets ore from the mountains.
    p1.placeRoad(&board.edges[10]); // p1 continues to build a road.
    p1.endTurn();                                    // p1 ends his turn.

    p2.rollDice(); // Lets say it's print 9. Then, p3 gets wool from the Pasture Land, p2 gets wool from the Pasture Land.
    p2.endTurn();  // p2 ends his turn.

    p3.rollDice(); // Lets say it's print 3. Then, p3 gets wheat from the Agricultural Land and Ore from the Mountains, p1 gets wheat from the Agricultural Land.
    p3.endTurn();  // p3 ends his turn.

    try
    {
        p2.rollDice(); // p2 tries to roll the dice again, but it's not his turn.
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }

    p1.rollDice();                       // Let's say it prints 6. Then, p1 gets bricks from the hills.
    p1.trade(p2, Resource::WOOD, 1, Resource::BRICK, 1);    // p1 trades 1 wood for 1 brick with p2.
    p1.endTurn();                        // p1 ends his turn.

    p2.rollDice();           // Lets say it's print 9. Then, p3 gets wool from the Pasture Land, p2 gets wool from the Pasture Land.
    p2.buyDevelopmentCard(); // p2 buys a development card. Lets say it is a bonus points card.
    p2.endTurn();            // p2 ends his turn.

    p1.printPoints(); // p1 has 2 points because it has two settelments.
    p2.printPoints(); // p2 has 3 points because it has two settelments and a bonus points card.
    p3.printPoints(); // p3 has 2 points because it has two settelments.

    board.printWinner(); // Should print None because no player reached 10 points.
}









