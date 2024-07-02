// minnesav@gmail.com

#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>

#include "Tile.hpp"
#include "Player.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"

class Board {
public:
    std::vector<Tile> tiles;
    std::vector<Player> players;
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;
    Player* longestRoadPlayer;
    Player* largestArmyPlayer;

    Board(); // Constructor

    void initializeBoard();
    void initializePlayers();
    void rollDice();
    void distributeResources(int rollResult);
    void handleRobber();
    void checkLongestRoad();
    void checkLargestArmy();

};

#endif // BOARD_HPP


