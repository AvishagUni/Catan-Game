// minnesav@gmail.com

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <map>
#include <vector>
#include <utility>

#include "Resource.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include "DevelopmentCard.hpp"
#include "PlayerAction.hpp"
#include "Board.hpp"

namespace Game {
    namespace Actions {
        class PlayerAction;
    }

    class Player {
    public:
        std::map<Resource, int> resources;
        std::vector<Vertex *> settlements;
        std::vector<Edge *> roads;
        std::vector<Vertex *> cities;
        int victoryPoints;
        std::vector<DevelopmentCard *> developmentCards;
        int playerID;
        int longestRoadLength;
        int knightsPlayed;
        Board *board;

        Player();

        bool canBuildSettlement(Vertex *vertex) const;

        bool canBuildRoad(Edge *edge) const;

        bool canBuildCity(Vertex *vertex) const;

        void buildSettlement(Vertex *vertex);

        void buildRoad(Edge *edge);

        void buildCity(Vertex *vertex);

        void addInitialSettlementsAndRoads(std::vector<Vertex *> initialSettlements, std::vector<Edge *> initialRoads);

        bool trade(Player &otherPlayer, Resource give, int giveAmount, Resource receive, int receiveAmount);

        void tradeWithBank(Resource give, int giveAmount, Resource receive);

        void useDevelopmentCard(int index);

        void playKnight();

        void displayResources() const;

        int calculateLongestRoad() const;

        void executeAction(PlayerAction *action);

    };
}

#endif // PLAYER_HPP




