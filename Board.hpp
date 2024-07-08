// minnesav@gmail.com

#ifndef BOARD_HPP
#define BOARD_HPP

#include "Tile.hpp"
#include "Node.hpp"
#include "Edge.hpp"

using namespace std;

class Tile;

class Board
{
    vector<Node> nodes;
    vector<Tile> tiles;
    vector<Edge> edges;

    vector<vector<int>> tile_data = {
    {0, 1, 2, 3, 4, 5}, // 0
    {6, 2, 7, 4, 8, 9}, // 1
    {10, 7, 11, 8, 12, 13}, // 2
    {3, 14, 5, 15, 16, 17}, // 3
    {4, 5, 9, 16, 18, 19}, // 4
    {8, 9, 13, 18, 20, 21}, // 5
    {12, 13, 22, 20, 23, 24}, // 6
    {15, 25, 17, 26, 27, 28}, // 7
    {16, 17, 19, 27, 29, 30}, // 8
    {18, 19, 21, 29, 31, 32}, // 9
    {20, 21, 24, 31, 33, 34}, // 10
    {23, 24, 35, 33, 36, 37}, // 11
    {27, 28, 30, 38, 39, 40}, // 12 
    {29, 30, 32, 39, 41, 42}, // 13
    {31, 32, 34, 41, 43, 44}, // 14
    {33, 34, 37, 43, 45, 46}, // 15
    {39, 40, 42, 47, 48, 49}, // 16
    {41, 42, 44, 48, 50, 51}, // 17
    {43, 44, 46, 50, 52, 53} // 18
};

    vector<pair<int, int>> edge_data = {
    {0, 1}, {0, 2}, {1, 3}, {2, 4}, {3, 5}, {4, 5}, {6, 2}, {6, 7}, {7, 8}, {4, 9}, {8, 9}, // 0-10
    {10, 7}, {10, 11}, {11, 12}, {12, 13}, {13, 8}, {14, 3}, {15, 14}, {16, 5}, {17, 16}, // 11-19
    {18, 21}, {19, 18}, {20, 21}, {21, 31}, {22, 23}, {23, 24}, {24, 33}, {25, 26}, {26, 28}, // 20-28
    {27, 30}, {28, 27}, {29, 32}, {30, 29}, {31, 34}, {32, 31}, {33, 37}, {34, 33}, {35, 36}, // 29-37
    {36, 37}, {37, 45}, {38, 40}, {39, 42}, {40, 39}, {41, 44}, {42, 41}, {43, 46}, {44, 43}, // 38-46
    {45, 46}, {46, 52}, {47, 49}, {48, 49}, {53, 52}, {50, 53}, {15, 17}, {16, 19}, {9, 18}, // 47-55
    {13, 20}, {12, 22}, {20, 24}, {23, 35}, {25, 15}, {17, 27}, {19, 29}, {28, 38}, {30, 39}, // 56-64
    {32, 41}, {34, 43}, {40, 47}, {42, 48}, {50, 51}, {44, 50}, {48, 51} // 65-71
};

vector<Tile> initializeTiles(int numTiles, vector<Node> &nodes, const vector<vector<int>> &tileData); // Initialize the tiles
vector<Node> initializeNodes(int numNodes, const vector<pair<int, int>> &edgeData, vector<Edge> &edges); // Initialize the nodes
vector<Edge> initializeEdges(int numEdges, const vector<pair<int, int>> &edgeData); // Initialize the edges

public:

Board(); // Constructor
~Board(); // Destructor

Tile* getTile(int i); // Get a tile
Node* getNode(int i); // Get a node
Edge* getEdge(int i); // Get an edge

vector<Tile> getTiles(); // Get the tiles
vector<Node> getNodes(); // Get the nodes
vector<Edge> getEdges(); // Get the edges

};

#endif // BOARD_HPP
