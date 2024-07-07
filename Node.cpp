#include <iostream>
#include <vector>
#include "Node.hpp"

using namespace std;

Node::Node(int i) : id(i) {
    owner = nullptr;
    type = "";
    val = 0;
    this->adjNodes = {};
    this->adjEdges = {};
}

string Node::getType()
{
    return type;
}

void Node::setType()
{
    if (type == "") {
        type = "Settlement";
        val = 1; }
    else if (type == "Settlement") {
        type = "City";
        val = 2; }
    }

Player* Node::getOwner()
{
    return owner;
}

void Node::setOwner(Player* o)
{
    owner = o;
}

vector<Node *> Node::getAdjSettlements()
{
    return adjNodes;
}

vector<Edge *> Node::getAdjRoads()
{
    return adjEdges;
}

int Node::getId() const
{
    return id;
}

int Node::getVal()
{
    return val;
}

void Node::addNeighbour(Node* n)
{
    adjNodes.push_back(n);
}

void Node::addEdge(Edge* e)
{
    adjEdges.push_back(e);
}




