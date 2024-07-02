#include "HexTile.hpp"


// EmptyTile render implementation
std::string EmptyTile::render(int line) {
    switch (line) {
    case 0: return " _____ ";
    case 1: return "/     \\";
    case 2: return "|     |";
    case 3: return "\\_____/";
    default: return "";
    }
}

// SettledTile render implementation
std::string SettledTile::render(int line) {
    switch (line) {
    case 0: return " _____ ";
    case 1: return "/     \\";
    case 2: return "| " + owner + " S |";
    case 3: return "\\_____/";
    default: return "";
    }
}

// CityTile render implementation
std::string CityTile::render(int line) {
    switch (line) {
    case 0: return " _____ ";
    case 1: return "/     \\";
    case 2: return "| " + owner + " C |";
    case 3: return "\\_____/";
    default: return "";
    }
}

