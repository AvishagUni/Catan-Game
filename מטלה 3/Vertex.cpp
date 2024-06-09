// minnesav@gmail.com

#include "Vertex.hpp"

Vertex::Vertex() : hasSettlement(false), hasCity(false), owner(-1) {}

void Vertex::placeSettlement(int playerID) {
    if (!hasSettlement && !hasCity ) {
        hasSettlement = true;
        owner = playerID;
    }
}

void Vertex::placeCity(int playerID) {
    if (hasSettlement && owner == playerID) {
        hasSettlement = false;
        hasCity = true;
    }
}

