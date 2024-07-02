// minnesav@gmail.com

#include "Edge.hpp"

Edge::Edge() : hasRoad(false), owner(-1) {}

void Edge::placeRoad(int playerID) {
    if (!hasRoad) {
        hasRoad = true;
        owner = playerID;
    }
}

