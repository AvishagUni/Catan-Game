#include <iostream>
#include <vector>
#include "Node.hpp"

using namespace std;

Node::Node(int i) : id(i) {
    owner = -1;
    type = "";
    this->neighbours = {0, 0, 0, 0, 0, 0};
}

string Node::getType()
{
    return type;
}

void Node::setType()
{
    if (type == "")
        type = "Settlement";
    else if (type == "Settlement")
        type = "City";
    }

int Node::getOwner()
{
    return owner;
}

void Node::setOwner(int playerNumber)
{
    owner = playerNumber;
}

vector<Node *> Node::getNeighbours()
{
    return neighbours;
}

// void Node::setNeighbour(Node *node)
// {
//     neighbours.push_back(node);
// }

int Node::getId() const
{
    return id;
}




