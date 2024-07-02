// minnesav@gmail.com

#ifndef TILE_HPP
#define TILE_HPP

#include <vector>

namespace Game {

    enum class Resource {
        WOOD,
        BRICK,
        WOOL,
        OATS,
        IRON,
        NONE };

    class Vertex;
    class Edge;

    class Tile {
    public:
        enum class TileType { FOREST, HILLS, PASTURE, FIELDS, MOUNTAINS, DESERT };

        Tile(TileType type, int number);

        int number;
        TileType type;
        std::vector<Vertex*> vertices;
        std::vector<Edge*> edges;

        virtual Resource getResource() const = 0;
        // virtual ~Tile() {}
    };

    class ForestTile : public Tile {
    public:
        ForestTile(int number) : Tile(TileType::FOREST, number) {}
        Resource getResource() const override {
            return Resource::WOOD;
        }
    };

    class HillsTile : public Tile {
    public:
        HillsTile(int number) : Tile(TileType::HILLS, number) {}
        Resource getResource() const override {
            return Resource::BRICK;
        }
    };

    class PastureTile : public Tile {
    public:
        PastureTile(int number) : Tile(TileType::PASTURE, number) {}
        Resource getResource() const override {
            return Resource::WOOL;
        }
    };

    class FieldsTile : public Tile {
    public:
        FieldsTile(int number) : Tile(TileType::FIELDS, number) {}
        Resource getResource() const override {
            return Resource::OATS;
        }
    };

    class MountainsTile : public Tile {
    public:
        MountainsTile(int number) : Tile(TileType::MOUNTAINS, number) {}
        Resource getResource() const override {
            return Resource::IRON;
        }
    };

    class DesertTile : public Tile {
    public:
        DesertTile(int number) : Tile(TileType::DESERT, number) {}
        Resource getResource() const override {
            return Resource::NONE;
        }
    };

}

#endif // TILE_HPP




