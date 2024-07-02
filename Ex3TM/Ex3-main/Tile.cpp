// minnesav@gmail.com

#include "Tile.hpp"

using namespace std;
using namespace Game;

Tile::Tile(TileType type, int number) : number(number), type(type) {
    vertices.resize(6, nullptr);
    edges.resize(6, nullptr);
}

    Resource Tile::getResource() const {
        switch (type) {
            case TileType::FOREST:
                return Resource::WOOD;
            case TileType::HILLS:
                return Resource::BRICK;
            case TileType::PASTURE:
                return Resource::WOOL;
            case TileType::FIELDS:
                return Resource::OATS;
            case TileType::MOUNTAINS:
                return Resource::IRON;
            case TileType::DESERT:
            default:
                return Resource::NONE;
        }
    }

