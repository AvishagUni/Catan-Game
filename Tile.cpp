// minnesav@gmail.com

#include "Tile.hpp"

// Constructor
Tile::Tile(int i, int num, Resource res) : id(i), number(num), resource(res) {
    nodes = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}; // Initialize nodes to nullptr
}

// Method to add nodes to the tile
void Tile::addNodes(const vector<Node*>& nodes2) {
    for (int i = 0; i < 6; i++) {
        nodes[i] = nodes2[i]; // Assign nodes from nodes2 vector
    }
}

// Getter for the number attribute
int Tile::getNumber() const {
    return number;
}

// Getter for the resource attribute
Resource Tile::getResource() const {
    return resource;
}

// Getter for the id attribute
int Tile::getId() const {
    return id;
}

// Method to get IDs of connected nodes
vector<size_t> Tile::getNodes() {
    vector<size_t> node_ids;
    for (int i = 0; i < 6; i++) {
        if (nodes[i] != nullptr) {
            node_ids.push_back(nodes[i]->getId()); // Add IDs of connected nodes to vector
        }
    }
    return node_ids;
}

