#include "Board.hpp"

using namespace std;

Board::Board()
{
    nodes = initializeNodes(54);
    tiles = initializeTiles(19, nodes, tile_data);
    edges = initializeEdges(72);
}

// Function to initialize nodes
vector<Node> initializeNodes(int numNodes)
{
    vector<Node> nodes;
    for (int i = 0; i < numNodes; i++)
    {
        nodes.push_back(Node(i));
    }
    return nodes;
}

// Function to initialize tiles
vector<Tile> initializeTiles(int numTiles, vector<Node> &nodes, const vector<vector<int>> &tileData)
{
    vector<Tile> tiles;
    vector<int> tileNums = {10, 2, 9, 12, 6, 4, 10, 9, 11, 7, 3, 8, 8, 3, 4, 5, 5, 6, 11};
    vector<string> tileResources = {"ore", "wool", "lumber", "grain", "brick", "wool", "brick", "grain", "lumber", "ore", "lumber", "ore", "lumber", "ore", "grain", "wool", "brick", "grain", "wool"};
    for (int i = 0; i < numTiles; i++)
    {
        tiles.push_back(Tile(i, tileNums[i], tileResources[i]));

        vector<Node *> nodes2;
        for (int j = 0; j < 6; j++)
        {
            nodes2.push_back(&nodes[tileData[i][j]]);
        }

        tiles[i].addNodes(nodes2);
    }
    return tiles;
}

// Function to initialize edges
vector<vector<Edge>> initializeEdges(int numNodes, const vector<pair<int, int>> &edgeData)
{
    vector<vector<Edge>> edges(numNodes, vector<Edge>(numNodes));
    for (auto edge : edgeData)
    {
        edges[edge.first][edge.second].setOwner(-1); // PlayerID -1
    }
    return edges;
}

