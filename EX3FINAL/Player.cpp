#include "Player.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

Player::Player(std::string name, int wood, int bricks, int grain, int wool, int ore, int vp)
    : name(name), wood(wood), bricks(bricks), grain(grain), wool(wool), ore(ore), victoryPoints(vp), knights(0) {}

std::string Player::getName() { return name; }

int Player::getVictoryPoints() { return victoryPoints; }
int Player::getKnights() { return knights; }

void Player::modifyVictoryPoints(int vp) { victoryPoints += vp; }
void Player::modifyKnights(int k) { knights += k; }

void Player::addDevelopmentCard(Card* card) {
    developmentCards.push_back(card);
}

void Player::useDevelopmentCard(CardType type, std::vector<Tile*>& island, std::vector<Player*>& players) {
    auto it = std::find_if(developmentCards.begin(), developmentCards.end(), [type](Card* card) { return card->getType() == type; });
    if (it != developmentCards.end()) {
        (*it)->use(*this, island, players);  // Use the card
        developmentCards.erase(it);  // Remove the used card from the player's deck
    }
}

int Player::getResource(ResourceType type) {
    switch (type) {
        case ResourceType::Wood:
            return wood;
        case ResourceType::Brick:
            return bricks;
        case ResourceType::Grain:
            return grain;
        case ResourceType::Wool:
            return wool;
        case ResourceType::Ore:
            return ore;
        default:
            return 0; // Default case if an invalid resource type is provided
    }
}

void Player::modifyResource(ResourceType type, int amount) {
    switch (type) {
        case ResourceType::Wood:
            wood += amount;
            break;
        case ResourceType::Brick:
            bricks += amount;
            break;
        case ResourceType::Grain:
            grain += amount;
            break;
        case ResourceType::Wool:
            wool += amount;
            break;
        case ResourceType::Ore:
            ore += amount;
            break;
        default:
            throw std::invalid_argument("Invalid resource type");
    }
}















