#include "Catan.hpp"
#include <cstdlib>
#include <ctime>
#include <algorithm>

namespace ariel
{
    Catan::Catan(Player &p1, Player &p2, Player &p3)
        : player1(p1), player2(p2), player3(p3), currentPlayer(&p1),
          longestRoadPlayer(nullptr), largestArmyPlayer(nullptr),
          longestRoadLength(0), largestArmySize(0), turn(1)
    {
        players.push_back(&p1);
        players.push_back(&p2);
        players.push_back(&p3);
        srand(time(0));
    }

    void Catan::ChooseStartingPlayer()
    {
        currentPlayer = &player1;
        std::cout << "Starting player is: " << currentPlayer->getName() << std::endl;
    }

    Board &Catan::getBoard()
    {
        return board;
    }

   void Catan::nextTurn()
    {
    if (currentPlayer == &player1)
        currentPlayer = &player2;
    else if (currentPlayer == &player2)
        currentPlayer = &player3;
    else
        currentPlayer = &player1;

    std::cout << "Turn " << turn << " ends. Next turn begins for " << currentPlayer->getName() << std::endl;
    turn++;
    }

    Player *Catan::getCurrentPlayer()
    {
        return currentPlayer;
    }

    void Catan::printWinner()
    {
        if (player1.getPoints() >= 10)
            std::cout << player1.getName() << " wins!" << std::endl;
        else if (player2.getPoints() >= 10)
            std::cout << player2.getName() << " wins!" << std::endl;
        else if (player3.getPoints() >= 10)
            std::cout << player3.getName() << " wins!" << std::endl;
        else
            std::cout << "No winner yet." << std::endl;
    }

    void Catan::distributeResources(int roll)
    {
        std::cout << "Distributing resources for roll: " << roll << std::endl;
        for (const auto& tile : board.getHexTiles())
        {
            if (tile.getNumberToken() == roll)
            {
                std::string resource;
                if (tile.getType() == "Forest") resource = "wood";
                else if (tile.getType() == "Hills") resource = "brick";
                else if (tile.getType() == "Fields") resource = "grain";
                else if (tile.getType() == "Mountains") resource = "ore";
                else if (tile.getType() == "Pasture") resource = "wool";

                std::cout << "Resource " << resource << " distributed to players with adjacent settlements/cities." << std::endl;

                // Distribute resources to players with adjacent settlements/cities
                for (auto &player : {&player1, &player2, &player3})
                {
                    for (const auto &settlement : player->getSettlements())
                    {
                        if (settlement.first == tile.getType() && settlement.second == tile.getNumberToken())
                        {
                            player->addResource(resource, 1);
                        }
                    }
                    for (const auto &city : player->getCities())
                    {
                        if (city.first == tile.getType() && city.second == tile.getNumberToken())
                        {
                            player->addResource(resource, 2); // Cities receive double resources
                        }
                    }
                }
            }
        }
    }

    void Catan::setupGame()
    {
        std::vector<std::string> initialPlaces = {"Forest", "Hills"};
        std::vector<int> initialNumbers = {5, 6};

        player1.placeRoad(initialPlaces);
        player1.placeSettlement(initialPlaces, initialNumbers);

        initialPlaces = {"Agricultural Land", "Desert"};
        initialNumbers = {3, 4};

        player1.placeRoad(initialPlaces);
        player1.placeSettlement(initialPlaces, initialNumbers);

        initialPlaces = {"Mountains", "Pasture Land"};
        initialNumbers = {4, 9};

        player2.placeRoad(initialPlaces);
        player2.placeSettlement(initialPlaces, initialNumbers);

        initialPlaces = {"Forest", "Pasture Land"};
        initialNumbers = {5, 9};

        player2.placeRoad(initialPlaces);
        player2.placeSettlement(initialPlaces, initialNumbers);

        initialPlaces = {"Mountains", "Pasture Land"};
        initialNumbers = {3, 8};

        player3.placeRoad(initialPlaces);
        player3.placeSettlement(initialPlaces, initialNumbers);

        initialPlaces = {"Agricultural Land", "Pasture Land"};
        initialNumbers = {3, 9};

        player3.placeRoad(initialPlaces);
        player3.placeSettlement(initialPlaces, initialNumbers);

    }

void Catan::updateLongestRoad(Player &player, int roadLength)
{
    if (roadLength >= 5 && roadLength > longestRoadLength)
    {
        if (longestRoadPlayer != &player)
        {
            std::cout << player.getName() << " now has the longest road with " << roadLength << " segments." << std::endl;
            longestRoadPlayer = &player;
            longestRoadLength = roadLength;
            player.addPoints(2); // Assuming the player gets 2 points for the longest road
        }
    }
    else if (longestRoadPlayer == &player && roadLength < longestRoadLength)
    {
        std::cout << player.getName() << " no longer has the longest road." << std::endl;
        longestRoadPlayer = nullptr;
        longestRoadLength = 0;
        player.addPoints(-2); // Assuming the player loses 2 points for losing the longest road
    }
}


    void Catan::updateLargestArmy(Player &player, int armySize)
    {
        if (armySize > largestArmySize)
        {
            largestArmySize = armySize;
            largestArmyPlayer = &player;
            std::cout << player.getName() << " has the largest army with " << armySize << " knights." << std::endl;
        }
    }

    const std::vector<Player *> &Catan::getPlayers() const
    {
        return players;
    }

    int Catan::getTurn() const
    {
        return turn;
    }

} // namespace ariel







