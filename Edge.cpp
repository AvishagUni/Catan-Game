#include "Edge.hpp"

Edge::Edge(int i) : id(i)
{
    owner = nullptr;
    this->adjNodes = {};
}

Edge::~Edge()
{
    for (int i = 0; i < 2; i++)
    {
        delete adjNodes[i];
    }
}


Player* Edge::getOwner()
{
    return owner;
}

void Edge::setOwner(Player* o)
{
    owner = o;
}

vector<Node *> Edge::getAdjSettlements()
{
    return adjNodes;
}

void Edge::setAdjSettlements(Node* n1, Node* n2)
{
    adjNodes.push_back(n1);
    adjNodes.push_back(n2);
}
