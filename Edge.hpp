// minnesav@gmail.com

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

    Edge(int i); // Constructor
    ~Edge() = default; // Destructor

    Player* getOwner() const; // Get the owner of the edge
    void setOwner(Player* o); // Set the owner of the edge

    vector<Node *> getAdjSettlements(); // Get the adjacent settlements
    void setAdjSettlements(Node* n1, Node* n2); // Set the adjacent settlements
};

#endif // EDGE_HPP
