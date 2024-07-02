#ifndef CATAN_HPP
#define CATAN_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include "HexTile.hpp"
#include "Player.hpp"
#include "DevelopmentCard.hpp"

using namespace std;

// Function declarations
void diceRoll(vector<Player*>& players, vector<Tile*>& island);
void buildIsland(vector<Tile*>& island);
void renderIsland(vector<Tile*> island);
void initializePlayers(vector<Player*> &players);
void resources(vector<Player*>& players, int z);
void buyRoad(vector<Player*>& players, vector<Tile*>& island, int player);
void buySettlement(vector<Player*>& players, vector<Tile*>& island, int player);
void buyDevelopmentCard(vector<Player*>& players, int player);
void buyCity(vector<Player*>& players, vector<Tile*>& island, int player);
void buyPrompt(vector<Player*>& players, vector<Tile*>& island, int player);
void tradePrompt(vector<Player*>& players, int player);
int selectTradePartner(vector<Player*>& players, int player);
ResourceType selectResource(const string& action);
int selectAmount(const string& action, vector<Player*>& players, int player, ResourceType rsrc);
void swapResources(vector<Player*>& players, int player);
bool confirmTrade(vector<Player*>& players, int player, int playerChoice, ResourceType giveRsrc, int giveAmt, ResourceType recRsrc, int recAmt);
void executeTrade(vector<Player*>& players, int player, int playerChoice, ResourceType giveRsrc, int giveAmt, ResourceType recRsrc, int recAmt);
bool hasSufficientResources(vector<Player*>& players, int player);
int takeTurn(vector<Player*>& players, vector<Tile*>& island, int player);
std::string getResourceName(ResourceType rsrc);
void buildTwoRoads(Player& player, vector<Tile*>& island);
void takeTwoResources(Player& player);
void takeAllResourcesOfOneType(Player& player, vector<Player*>& players);

#endif // CATAN_HPP






