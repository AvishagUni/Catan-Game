#include "Player.hpp"

Player::Player(string name) : name(name), points(0) {
    settlements = {};
    cities = {};
    roads = {};
    resources = {0, 0, 0, 0, 0}; // {Brick, Grain, Lumber, Ore, Wool}
    cards = {0, 0, 0, 0, 0}; // {VictoryPoint, Knight, RoadBuilding, YearofPlenty, Monopoly}
}

Player::~Player() {
    settlements.clear();
    cities.clear();
    roads.clear();
    resources.clear();
    cards.clear();
}

string Player::getName() {
    return name;
}

const vector<size_t>& Player::getResources() const {
    return resources;
}

const vector<size_t>& Player::getSettlements() const {
    return settlements;
}

const vector<size_t>& Player::getCities() const {
    return cities;
}

const vector<size_t>& Player::getRoads() const {
    return roads;
}

const vector<size_t>& Player::getCards() const {
    return cards;
}

size_t Player::getPoints() const {
    return points;
}

void Player::modifyPoints(int amount) {
    this->points += amount;
}

void Player::modifyResources(int amount, Resource resource) {
    this->resources[static_cast<size_t>(resource)] += amount;
}

size_t Player::stealResource(Resource resource) {
    int amount = this->resources[static_cast<size_t>(resource)];  
    resources[static_cast<size_t>(resource)] = 0;
    return amount;
}

bool Player::canBuyRoad() const
{
    if(this->resources[0] >= 1 && this->resources[2] >= 1)
    {
        return true;
    }
    return false;
}

bool Player::canBuySettlement() const
{
    if(this->resources[0] >= 1 && this->resources[1] >= 1 && this->resources[2] >= 1 && this->resources[4] >= 1)
    {
        return true;
    }
    return false;
}

bool Player::canBuyCity() const
{
    if(this->resources[1] >= 2 && this->resources[3] >= 3)
    {
        return true;
    }
    return false;
}

bool Player::canBuyDevelopmentCard() const
{
    if(this->resources[1] >= 1 && this->resources[3] >= 1 && this->resources[4] >= 1)
    {
        return true;
    }
    return false;
}

int Player::rollDice() const
{
    int dice1 = rand() % 6 + 1;
    int dice2 = rand() % 6 + 1;
    int sum = dice1 + dice2;
    return sum;
}

void Player::buyRoad(size_t idx) {
        resources[0] -= 1;
        resources[2] -= 1;
        roads.push_back(idx);
}

void Player::buySettlement(size_t idx) {
        resources[0] -= 1;
        resources[1] -= 1;
        resources[2] -= 1;
        resources[4] -= 1;
        settlements.push_back(idx);
        this->modifyPoints(1);
}

void Player::buyCity(size_t idx) {
        resources[1] -= 2;
        resources[3] -= 3;
        cities.push_back(idx);
        this->modifyPoints(1);
        }

void Player::buyDevelopmentCard() {
        resources[1] -= 1;
        resources[3] -= 1;
        resources[4] -= 1;
        int random = rand() % 5;
        cout << this->getName() << " bought a card of type " << random << endl;
        cards[random] += 1;
}

void Player::tradeWithPlayer(Player* player, const vector<size_t>& resourcesToGive, const vector<size_t>& resourcesToTake)
{
    if (resourcesToGive.size() != resourcesToTake.size() || resourcesToGive.size() != resources.size())
    {
        throw invalid_argument("Resource vectors must have the same size as the player's resources");
    }

    // Check if both players have enough resources to trade
    for (size_t i = 0; i < resourcesToGive.size(); i++)
    {
        if (this->resources[i] < resourcesToGive[i])
        {
            throw invalid_argument("Player initiating the trade does not have enough resources to give");
        }
        if (player->resources[i] < resourcesToTake[i])
        {
            throw invalid_argument("Player accepting the trade does not have enough resources to give");
        }
    }

    // Perform the trade
    for (size_t i = 0; i < resourcesToGive.size(); i++)
    {
        this->resources[i] -= resourcesToGive[i];
        player->resources[i] -= resourcesToTake[i];
        this->resources[i] += resourcesToTake[i];
        player->resources[i] += resourcesToGive[i];
    }

    cout << "Trade completed successfully" << endl;
} 

void Player::tradeWithBank(Resource resourceToGive, Resource resourceToTake)
{
    if (this->resources[static_cast<size_t>(resourceToGive)] < 4)
    {
        throw invalid_argument("Not enough resources to trade with the bank");
    }

    this->resources[static_cast<size_t>(resourceToGive)] -= 4;
    this->resources[static_cast<size_t>(resourceToTake)] += 1;
    cout << "Trade completed successfully" << endl;
}

size_t Player::getKnights() const
{
    return knights;
}

void Player::modifyKnights(int amount)
{
    knights += amount;
}

void Player::modifyCards(int amount, CardType card)
{
    size_t cardIndex = static_cast<size_t>(card);
    cards[cardIndex] += amount;
}

void Player::addRoad(int idx) {
    roads.push_back(idx);
}

void Player::addSettlement(int idx) {
    settlements.push_back(idx);
}








