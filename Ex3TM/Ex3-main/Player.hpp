// minnesav@gmail.com

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <map>
#include <vector>
#include <queue>

#include "Vertex.hpp"
#include "Edge.hpp"
#include "DevelopmentCard.hpp"
#include "Tile.hpp"
#include "Board.hpp"
#include "PlayerAction.hpp"


namespace Game {

    class DevelopmentCard;
    class PlayerAction;

    class Player {
    public:
        std::string name;
        std::map<Resource, int> resources;
        std::vector<Vertex *> settlements;
        std::vector<Edge *> roads;
        std::vector<Vertex *> cities;
        int victoryPoints;
        std::vector<DevelopmentCard*> developmentCards;
        int longestRoadLength;
        int knightsPlayed;
        Board *board;

        Player(const std::string& playerName);

        void placeInitialSettlementsAndRoads();

        void rollDice();

        void buyDevelopmentCard();

        bool placeSettlement(Vertex *vertex);

        bool placeRoad(Edge *edge);

        bool placeCity(Vertex *vertex);

        bool trade(Player &otherPlayer, Resource give, int giveAmount, Resource receive, int receiveAmount);

        void tradeWithBank(Resource give, int giveAmount, Resource receive);

        void useDevelopmentCard(int index); 

        void endTurn();

        void displayResources() const;

        int calculateLongestRoad() const;

        void printPoints() const;

        void executeAction(PlayerAction *action);

    };
}


#endif // PLAYER_HPP




