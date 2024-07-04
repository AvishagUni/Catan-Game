#include <string>
#include <vector>
#include <iostream>

#include "Node.hpp"

using namespace std;

class Tile
{
    int id;
    int number;
    string resource; 
    vector<Node *> nodes;

public:
    Tile(int i, int n, string r);
    ~Tile();

    void addNodes(const vector<Node *> &nodes2);

    string getNumber() const;
    string getResource() const;
    int getId() const;
    vector<size_t> &getNodes() ;
};