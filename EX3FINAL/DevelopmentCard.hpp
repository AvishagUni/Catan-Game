#ifndef DEVELOPMENT_CARD_HPP
#define DEVELOPMENT_CARD_HPP

#include "HexTile.hpp"
#include <vector>
#include "Player.hpp"

enum class CardType {
    VictoryPoint,
    Knight,
    RoadBuilding,
    YearOfPlenty,
    Monopoly
};

class Player;

class Card {
private:
    CardType type;

public:
    Card(CardType type) : type(type) {}
    CardType getType() const { return type; }
    virtual void use(Player& player, std::vector<Tile*>& island, std::vector<Player*>& players);
    virtual ~Card() = default; // Ensure a virtual destructor for proper cleanup
    };

#endif // DEVELOPMENT_CARD_HPP


