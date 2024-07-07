#include "Player.hpp"

class Edge
{
    int id;
    Player* owner;
    vector<Node *> adjNodes;

public:

    Edge(int i) : id(i) {}
    ~Edge();

    Player* getOwner();
    void setOwner(Player* o);

    vector<Node *> getAdjSettlements();
    void setAdjSettlements(Node* n1, Node* n2);
};
