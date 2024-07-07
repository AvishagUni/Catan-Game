#ifndef DEVELOPMENT_CARD_HPP
#define DEVELOPMENT_CARD_HPP

#include <vector>
#include "Player.hpp"
#include "Tile.hpp"

enum class CardType {
    VictoryPoint,
    Knight,
    RoadBuilding,
    YearOfPlenty,
    Monopoly
};

class Player;

class DevelopmentCard {
private:
    CardType type;

public:
    DevelopmentCard(CardType type) : type(type) {}
    CardType getType() const { return type; }
    virtual void use(Player &player, std::vector<Player*> &players);
    virtual ~DevelopmentCard() = default; // Ensure a virtual destructor for proper cleanup
    };

#endif // DEVELOPMENT_CARD_HPP


