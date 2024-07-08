#ifndef EDGE_HPP
#define EDGE_HPP

#include <vector>

class Node;
class Player;

using namespace std;

class Edge
{
    int id;
    Player* owner;
    vector<Node *> adjNodes;

public:

    Edge(int i);
    ~Edge() = default;

    Player* getOwner();
    void setOwner(Player* o);

    vector<Node *> getAdjSettlements();
    void setAdjSettlements(Node* n1, Node* n2);
};

#endif // EDGE_HPP
