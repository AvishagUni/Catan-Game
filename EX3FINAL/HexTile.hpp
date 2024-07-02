#ifndef HEXTILE_HPP
#define HEXTILE_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

enum LandType { FOREST, HILLS, FIELD, PASTURE, MOUNTAIN };

class Road {
public:
    string owner;
    int fromTile;
    int toTile;

    Road(string owner, int fromTile, int toTile) : owner(owner), fromTile(fromTile), toTile(toTile) {}
};

// The base class for all tiles
class Tile {
protected:
    LandType land;
    int number;
    string owner;
    std::vector<Road> roads; // Add roads to the tile

public:
    // Constructors
    Tile() : land(FOREST), number(0), owner("") {}
    virtual ~Tile() {} // Add this line for the virtual destructor
    Tile(LandType land, int number) : land(land), number(number), owner("") {}

    // Mutators and Accessors
    void setLand(LandType land) { this->land = land; }
    void setNumber(int number) { this->number = number; }
    void setOwner(string owner) { this->owner = owner; }
    LandType getLand() { return land; }
    int getNumber() { return number; }
    string getOwner() { return owner; }

    // Virtual function to render the tile's image in the terminal
    virtual std::string render(int) { return ""; }

    // Function to add a road
    bool addRoad(string owner, int fromTile, int toTile) {
        for (const Road& road : roads) {
            if (road.fromTile == fromTile && road.toTile == toTile) {
                return false; // Road already exists
            }
        }
        roads.emplace_back(owner, fromTile, toTile);
        return true;
    }

    // Function to check if a road exists
    bool hasRoad(string owner, int fromTile, int toTile) const {
        for (const Road& road : roads) {
            if (road.owner == owner && road.fromTile == fromTile && road.toTile == toTile) {
                return true;
            }
        }
        return false;
    }
};

class EmptyTile : public Tile {
public:
    EmptyTile(LandType land, int number) : Tile(land, number) {}
    std::string render(int line);
};

class SettledTile : public Tile {
public:
    SettledTile(LandType land, int number, string owner) : Tile(land, number) { this->owner = owner; }
    std::string render(int line);
};

class CityTile : public Tile {
public:
    CityTile(LandType land, int number, string owner) : Tile(land, number) { this->owner = owner; }
    std::string render(int line);
};

#endif // HEXTILE_HPP
