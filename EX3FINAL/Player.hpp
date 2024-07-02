#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include "DevelopmentCard.hpp"

enum class ResourceType {
    Wood,
    Brick,
    Grain,
    Wool,
    Ore,
    Invalid
};

class Player {
private:
    std::string name;
    int wood, bricks, grain, wool, ore, victoryPoints, knights;
    std::vector<Card*> developmentCards;

public:
    Player(std::string name, int wood, int bricks, int grain, int wool, int ore, int vp);

    std::string getName();

    int getVictoryPoints();
    int getKnights();

    void modifyVictoryPoints(int vp);
    void modifyKnights(int k);

    void addDevelopmentCard(Card* card);
    void useDevelopmentCard(CardType type, std::vector<Tile*>& island, std::vector<Player*>& players);

    int getResource(ResourceType type);
    void modifyResource(ResourceType type, int amount);
    };

#endif // PLAYER_HPP









