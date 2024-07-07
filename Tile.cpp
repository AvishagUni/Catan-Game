#include "Tile.hpp"

Tile::Tile(int i, int num, Resource res) : id(i) , number(num), resource(res) {
    nodes = {0, 0, 0, 0, 0, 0};
}

Tile::~Tile()
{
    for(int i = 0; i < 6; i++)
    {
        delete nodes[i];
    }
}

void Tile::addNodes(const vector<Node *> &nodes2)
{
    for (int i = 0; i < 6; i++)
    {
        nodes[i] = nodes2[i];
    }
}

int Tile::getNumber() const
{
    return number;
}

Resource Tile::getResource() const
{
    return resource;
}

int Tile::getId() const
{
    return id;
}

vector<size_t> &Tile::getNodes()
{
    vector<size_t> node_ids;
    for (int i = 0; i < 6; i++)
    {
        node_ids.push_back(nodes[i]->getId());
    }
    return node_ids;
}

