// minnesav@gmail.com

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <vector>
#include "DevelopmentCard.hpp"
#include "Board.hpp"
#include "Catan.hpp"
#include "CardType.hpp"

using namespace std;


class Player {
    string name;
    vector<size_t> cards; // {VictoryPoint, Knight, RoadBuilding, YearofPlenty, Monopoly}
    vector<size_t> resources; // {Brick, Grain, Lumber, Ore, Wool}
    vector<size_t> settlements;
    vector<size_t> cities;
    vector<size_t> roads;
    size_t points;
    size_t knights;

    public:
    Player(string name); // Constructor
    ~Player(); // Destructor

    bool canBuyRoad() const; // Check if the player can buy a road
    bool canBuySettlement() const; // Check if the player can buy a settlement
    bool canBuyCity() const; // Check if the player can buy a city
    bool canBuyDevelopmentCard() const; // Check if the player can buy a development card
    void buyRoad(size_t idx); // Buy a road
    void buySettlement(size_t idx); // Buy a settlement
    void buyCity(size_t idx); // Buy a city
    void buyDevelopmentCard(); // Buy a development card

    string getName(); // Get the name of the player
    const vector<size_t>& getResources() const; // Get the resources of the player
    const vector<size_t>& getSettlements() const; // Get the settlements of the player
    const vector<size_t>& getCities() const; // Get the cities of the player
    const vector<size_t>& getRoads() const; // Get the roads of the player
    const vector<size_t>& getCards() const; // Get the cards of the player
    size_t getPoints() const; // Get the points of the player
    size_t getKnights() const; // Get the knights of the player

    void modifyKnights(int amount); // Modify the knights of the player
    void modifyPoints(int amount); // Modify the points of the player
    void modifyResources(int amount, Resource resource); // Modify the resources of the player
    void modifyCards(int amount, CardType card); // Modify the cards of the player

    size_t stealResource(Resource resource); // for monopoly card
    void tradeWithPlayer(Player* player, const vector<size_t>& resourcesToGive, const vector<size_t>& resourcesToTake); // for trade with player
    void tradeWithBank(Resource resource1, Resource resource2); // for trade with bank 4:1

    void addRoad(int i); // Add a road
    void addSettlement(int i); // Add a settlement

    int rollDice() const; // Roll the dice

};

#endif // PLAYER_HPP
