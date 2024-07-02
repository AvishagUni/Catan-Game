#pragma once
#include <string>
#include <map>
#include <vector>
#include "Board.hpp"
#include "DevelopmentCard.hpp"

namespace ariel {
    class Player {
    public:
        std::string name;
        int points;
        int roadLength;
        int armySize;
        std::map<std::string, int> resources;
        std::vector<DevelopmentCard> developmentCards;
        std::vector<std::pair<std::string, int>> settlements;
        std::vector<std::pair<std::string, int>> cities;

        Player(const std::string& name);

        std::string getName() const;
        int getPoints() const;
        void addPoints(int p);

        bool canBuildRoad(const std::pair<std::string, std::string>& places, Board& board) const;
        bool canBuildSettlement(const std::string& place, Board& board) const;
        void placeSettlement(const std::vector<std::string>& places, const std::vector<int>& placesNum);
        void placeRoad(const std::vector<std::string>& places);
        int rollDice();
        void trade(Player& other, const std::string& give, const std::string& receive, int giveAmount, int receiveAmount);
        void tradeWithBank(const std::string& give, const std::string& receive);
        void buyDevelopmentCard();
        void useDevelopmentCard(CardType type);
        void printPoints() const;
        void endTurn();

        void addResource(const std::string& resource, int amount);
        bool buildSettlement(const std::vector<std::string>& places, Board& board);
        bool buildRoad(const std::vector<std::string>& places, Board& board);
        bool buildCity(const std::vector<std::string>& places);
        const std::vector<std::pair<std::string, int>>& getSettlements() const;
        const std::vector<std::pair<std::string, int>>& getCities() const;
        const std::vector<DevelopmentCard>& getDevelopmentCards() const;
        void incrementRoadLength(int length);
        void incrementArmySize();
        int getRoadLength() const;
        int getArmySize() const;
        int getResourceCount(const std::string& resource) const;
    };
}
