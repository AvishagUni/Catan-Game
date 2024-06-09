// minnesav@gmail.com

#ifndef TILE_HPP
#define TILE_HPP

#include <vector>

#include "Resource.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"

class Tile {
public:
    int number;
    std::vector<Vertex*> vertices;
    std::vector<Edge*> edges;

    Tile(int number) : number(number) {
        vertices.resize(6);
        edges.resize(6);
    }

    virtual Resource getResource() const = 0;
    virtual ~Tile() {}
};

class ForestTile : public Tile {
public:
    ForestTile(int number) : Tile(number) {}
    Resource getResource() const override {
        return Resource::WOOD;
    }
};

class HillsTile : public Tile {
public:
    HillsTile(int number) : Tile(number) {}
    Resource getResource() const override {
        return Resource::BRICK;
    }
};

class PastureTile : public Tile {
public:
    PastureTile(int number) : Tile(number) {}
    Resource getResource() const override {
        return Resource::WOOL;
    }
};

class FieldsTile : public Tile {
public:
    FieldsTile(int number) : Tile(number) {}
    Resource getResource() const override {
        return Resource::OATS;
    }
};

class MountainsTile : public Tile {
public:
    MountainsTile(int number) : Tile(number) {}
    Resource getResource() const override {
        return Resource::IRON;
    }
};

class DesertTile : public Tile {
public:
    DesertTile(int number) : Tile(number) {}
    Resource getResource() const override {
        return Resource::NONE;
    }
};

#endif // TILE_HPP

