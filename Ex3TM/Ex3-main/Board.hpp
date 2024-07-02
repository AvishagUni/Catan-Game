// minnesav@gmail.com

#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <memory>
#include <algorithm>  // for std::find
#include <stdexcept>  // for std::runtime_error
#include <iomanip> // For formatted output
#include "Tile.hpp"
#include "Dice.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include "Player.hpp"

namespace Game {

    class Player;  // Forward declaration

    class Board {

        public:

        Board();

        // initilization methods
        void initializeBoard();
        void initializePlayers();

        // Gameplay methods
        void distributeResources(int rollResult);
        void checkLongestRoad();
        void checkLargestArmy();
        void printWinner();

        std::vector<Edge> edges;
        std::vector<Player> players;
        std::vector<Vertex> vertices;
        std::vector<Tile*> tiles; 

        private:
        Player* longestRoadPlayer;
        Player* largestArmyPlayer;

        // Helper methods
        std::vector<Vertex*> getAdjacentVertices(size_t index);
        std::vector<Edge*> getAdjacentEdges(size_t index);
        std::vector<Vertex*> getAdjacentVerticesForEdge(size_t index);
        std::vector<Edge*> getAdjacentEdgesForEdge(size_t index);
};
}

#endif



