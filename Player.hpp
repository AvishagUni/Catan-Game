#include <iostream>
#include <vector>
#include "DevelopmentCard.hpp"


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
    Player(string name) : name(name), points(0) {}
    ~Player();

    bool canBuyRoad() const;
    bool canBuySettlement() const;
    bool canBuyCity() const;
    bool canBuyDevelopmentCard() const;
    void buyRoad(size_t idx);
    void buySettlement(size_t idx);
    void buyCity(size_t idx);
    void buyDevelopmentCard();

    string getName();
    const vector<size_t>& getResources() const;
    const vector<size_t>& getSettlements() const;
    const vector<size_t>& getCities() const;
    const vector<size_t>& getRoads() const;
    const vector<size_t>& getCards() const;
    size_t getPoints() const;
    size_t getKnights() const;

    void modifyKnights(int amount); 
    void modifyPoints(int amount);
    void modifyResources(int amount, Resource resource);
    void modifyCards(int amount, CardType card);

    size_t stealResource(Resource resource); // for monopoly card
    void tradeWithPlayer(Player* player, const vector<size_t>& resourcesToGive, const vector<size_t>& resourcesToTake);
    void tradeWithBank(Resource resource1, Resource resource2);

    int rollDice() const;
    void endTurn() const;

};