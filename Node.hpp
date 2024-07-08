// minnesav@gmail.com

#ifndef NODE_HPP
#define NODE_HPP

#include "Player.hpp"
#include "Edge.hpp"

class Node
{
    int id;
    Player* owner;
    string type;
    int val;
    vector<Node *> adjNodes;
    vector<Edge *> adjEdges;

public:
    Node(int i); // Constructor

    string getType(); // Get the type of the node, i.e. settlement, city, or empty
    void setType(); // Set the type of the node

    int getVal();   // Get the value of the node (0-2)

    Player* getOwner(); // Get the owner of the node
    void setOwner(Player* o); // Set the owner of the node

    int getId() const; // Get the id of the node

    void addNeighbour(Node* n); // Add a neighbouring node
    void addEdge(Edge* e); // Add an edge to the node
    
    vector<Node *> getAdjSettlements(); // Get the adjacent settlements
    vector<Edge *> getAdjRoads(); // Get the adjacent roads
};

#endif // NODE_HPP
