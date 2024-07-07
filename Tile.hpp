#include <string>
#include <vector>
#include <iostream>

#include "Node.hpp"

using namespace std;

enum class Resource
{
    BRICK,
    GRAIN,
    LUMBER,
    ORE,
    WOOL
};

class Tile
{
    int id;
    int number;
    Resource resource; 
    vector<Node *> nodes;

public:
    Tile(int i, int num, Resource res);
    ~Tile();

    void addNodes(const vector<Node *> &nodes2);

    int getNumber() const;
    Resource getResource() const;
    int getId() const;
    vector<size_t> &getNodes() ;
};
