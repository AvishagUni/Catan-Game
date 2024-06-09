// minnesav@gmail.com

#include "Dice.hpp"

Dice::Dice() {
    std::srand(std::time(0));
}

int Dice::roll() {
    return std::rand() % 6 + 1 + std::rand() % 6 + 1;
}
