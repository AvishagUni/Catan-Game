// minnesav@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Board.hpp"
#include "Player.hpp"

Player* player1 = new Player("Avishag");
Player* player2 = new Player("Yael");
Player* player3 = new Player("Shir");

Catan game(player1, player2, player3);
Board* board = game.getBoard();

TEST_CASE("Board Initialization") {

    CHECK(board->getTiles().size() == 19);
    CHECK(board->getNodes().size() == 54);
    CHECK(board->getEdges().size() == 72);

    Tile* tile = board->getTile(0);
    CHECK(tile->getNumber() == 10);
    CHECK(tile->getResource() == Resource::ORE);
}

TEST_CASE("Player Initialization") {

    CHECK(player1->getName() == "Avishag");
    CHECK(player1->getPoints() == 0);
    CHECK(player1->getResources().size() == 5); // {Brick, Grain, Lumber, Ore, Wool}
}

TEST_CASE("Build Road and Settlement") {

    // 55 is the edge between nodes 9 and 18
    CHECK_THROWS(game.buildRoad(55, player1, true)); // no adjacent settlement

    game.buildSettlement(9, player1, true);
    CHECK(player1->getSettlements()[0] == 9);

    game.buildRoad(55, player1, true);
    CHECK(player1->getRoads()[0] == 55);

    // Verify road and settlement ownership 
    Edge* edge = board->getEdge(55);
    CHECK(edge->getOwner() == player1);

    Node* node = board->getNode(9);
    CHECK(node->getOwner() == player1);
}

TEST_CASE("Build Settlement") {

    game.buildSettlement(23, player2, true); 
    CHECK(player2->getSettlements()[0] == 23);

    // Verify settlement ownership
    Node* node = board->getNode(23);
    CHECK(node->getOwner() == player2);
}

TEST_CASE("Build City") {

    player2->modifyResources(3, Resource::ORE);
    player2->modifyResources(2, Resource::GRAIN);

    game.buildCity(23, player2);
    CHECK(player2->getCities()[0] == 23);

    // Verify city ownership
    Node* node = board->getNode(23);
    CHECK(node->getOwner() == player2);
}

TEST_CASE("Resource Distribution") {

    // Assume player has a settlement on node 0, which is adjacent to tile 0
    game.buildSettlement(0, player3, true);

    // Simulate a dice roll that activates tile 0
    int tile0DiceNumber = 10; 
    game.distributeResources(tile0DiceNumber);

    // Verify the player received the correct resource
    CHECK(player3->getResources()[3] == 1); 
}

TEST_CASE("Player to Player Trade") {

    // Assume initial resources
    player1->modifyResources(1, Resource::ORE);
    player2->modifyResources(1, Resource::GRAIN);

    // Execute trade
    player1->tradeWithPlayer(player2, {0, 0, 0, 1, 0}, {0, 1, 0, 0, 0});

    // Verify resource counts after trade
    CHECK(player1->getResources()[3] == 0);
    CHECK(player1->getResources()[1] == 1);
    CHECK(player2->getResources()[1] == 0);
    CHECK(player2->getResources()[3] == 1);
}

TEST_CASE("Player to Bank Trade") {
    
        // Assume initial resources
        player1->modifyResources(1, Resource::ORE);
    
        CHECK_THROWS(player1->tradeWithBank(Resource::ORE, Resource::LUMBER)); // not enough resources 4:1

        // Execute trade
        player1->modifyResources(3, Resource::ORE);
        player1->tradeWithBank(Resource::ORE, Resource::LUMBER);
    
        // Verify resource counts after trade
        CHECK(player1->getResources()[3] == 0);
        CHECK(player1->getResources()[2] == 1);
}

TEST_CASE("Development Card Test") {

    // Assume initial resources
    player3->modifyResources(1, Resource::ORE);
    player3->modifyResources(1, Resource::GRAIN);
    player3->modifyResources(1, Resource::WOOL);

    player3->buyDevelopmentCard();

    game.useDevelopmentCard(player3);
    // Verify resource counts after buying development card
    CHECK(player3->getResources()[3] == 1);
    CHECK(player3->getResources()[1] == 0);
    CHECK(player3->getResources()[4] == 0);
}

TEST_CASE("Win Condition Test") {

    // Assume player has 10 points
    player3->modifyPoints(10);
    game.checkWinCondition();
    CHECK(player3->getName() == "Shir");

    // Assume no player has 10 points
    player3->modifyPoints(-10);
    game.checkWinCondition();
    CHECK("The game ended with a tie...");
}

TEST_CASE("Largest Army Test") {

    // Assume player has 3 knights
    player1->modifyKnights(3);
    game.checkLargestArmy();
    CHECK(player1->getPoints() == 2);
}

TEST_CASE("Build on Existing Settlement") {

    // settlement already occupied by player2
    CHECK_THROWS(game.buildSettlement(23, player1, true)); // settlement already exists

}

TEST_CASE("Invalid Moves") {

    // Attempt to build a road not in range
    CHECK_THROWS(game.buildRoad(73, player1, true)); // road doesn't exist

    // Attempt to build a settlement not in range
    CHECK_THROWS(game.buildSettlement(55, player1, true)); // settlement doesn't exist

}






