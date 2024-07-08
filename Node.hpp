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
    Node(int i);

    string getType();
    void setType();

    int getVal();

    Player* getOwner();
    void setOwner(Player* o);

    int getId() const;

    void addNeighbour(Node* n);
    void addEdge(Edge* e);
    
    vector<Node *> getAdjSettlements();
    vector<Edge *> getAdjRoads();
};

#endif // NODE_HPP
