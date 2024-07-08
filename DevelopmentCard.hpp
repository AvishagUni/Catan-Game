// minnesav@gmail.com

#ifndef DEVELOPMENT_CARD_HPP
#define DEVELOPMENT_CARD_HPP

#include <vector>
#include "Player.hpp"
#include "Tile.hpp"
#include "CardType.hpp"

class Player;

class DevelopmentCard {
private:
    CardType type;

public:
    DevelopmentCard(CardType type) : type(type) {} // Constructor
    CardType getType() const { return type; } // Get the type of the card
    virtual void use(Player &player, std::vector<Player*> &players); // Use the card
    virtual ~DevelopmentCard() = default; // Ensure a virtual destructor for proper cleanup
    };

#endif // DEVELOPMENT_CARD_HPP


