#include "Board.hpp"
#include <map>

using namespace std;

Board::Board()
{
    nodes = initializeNodes(54, edge_data, edges);
    tiles = initializeTiles(19, nodes, tile_data);
    edges = initializeEdges(72, edge_data);
}

Board::~Board()
{
    nodes.clear();
    tiles.clear();
    edges.clear();
}

std::vector<Node> Board::initializeNodes(int numNodes, const std::vector<std::pair<int, int>>& edgeData, std::vector<Edge>& edges) {
    std::vector<Node> nodes;

    // Create nodes
    for (int i = 0; i < numNodes; i++) {
        nodes.push_back(Node(i));
    }

    // Initialize edges and set up adjacency lists
    for (size_t i = 0; i < edgeData.size(); ++i) {
        int node1 = edgeData[i].first;
        int node2 = edgeData[i].second;

        edges.push_back(Edge(i));
        edges[i].setAdjSettlements(&nodes[node1], &nodes[node2]);
        nodes[node1].addNeighbour(&nodes[node2]);
        nodes[node2].addNeighbour(&nodes[node1]);

        nodes[node1].addEdge(&edges[i]);
        nodes[node2].addEdge(&edges[i]);
    }

    return nodes;
}

// Function to initialize tiles
vector<Tile> Board::initializeTiles(int numTiles, vector<Node> &nodes, const vector<vector<int>> &tileData)
{
    vector<Tile> tiles;
    vector<int> tileNums = {10, 2, 9, 12, 6, 4, 10, 9, 11, 7, 3, 8, 8, 3, 4, 5, 5, 6, 11};
    vector<Resource> tileResources = {Resource::ORE, Resource::WOOL, Resource::LUMBER, Resource::GRAIN, Resource::BRICK, Resource::WOOL, Resource::BRICK, Resource::GRAIN, Resource::LUMBER, Resource::ORE, Resource::LUMBER, Resource::ORE, Resource::LUMBER, Resource::ORE, Resource::GRAIN, Resource::WOOL, Resource::BRICK, Resource::GRAIN, Resource::WOOL};
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
vector<Edge> Board::initializeEdges(int numEdges, const vector<pair<int, int>> &edgeData)
{
    vector<Edge> edges;
    for (int i =0 ; i < numEdges; i++)
    {
        edges.push_back(Edge(i));

        Node* node1 = &nodes[edgeData[i].first];
        Node* node2 = &nodes[edgeData[i].second];

        edges[i].setAdjSettlements(node1, node2);
    }
    return edges;
}

// Function to get a tile
Tile *Board::getTile(int i)
{
    return &tiles[i];
}

// Function to get a node
Node *Board::getNode(int i)
{
    return &nodes[i];
}

// Function to get an edge
Edge *Board::getEdge(int i)
{
    return &edges[i];
}

vector<Tile> Board::getTiles()
{
    return tiles;
}

vector<Node> Board::getNodes()
{
    return nodes;
}

vector<Edge> Board::getEdges()
{
    return edges;
}

