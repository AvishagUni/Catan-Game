#include "Catan.hpp"

// Global variables
int player = 0;
int choice = 0;
int roll = 0;

void diceRoll(vector<Player*>& players, vector<Tile*>& island) {
    int roll = (rand() % 11) + 2; // Generate a random roll between 2 and 12 (inclusive)
    cout << endl;
    cout << "\t\t\tDice roll: " << roll << endl;
    cout << "\t\t\t";

    // Iterate through each tile on the island
    for (Tile* tile : island) {
        std::string owner = tile->getOwner();
        if (!owner.empty() && roll == tile->getNumber()) {
            int resources = (owner.size() > 10) ? 2 : 1; // Cities get double resources
            if (owner.size() > 10) owner = owner.substr(0, 10); // Normalize city owner value

            // Allocate resources based on the type of land
            ResourceType resourceType;
            switch (tile->getLand()) {
                case FOREST:
                    resourceType = ResourceType::Wood;
                    break;
                case HILLS:
                    resourceType = ResourceType::Brick;
                    break;
                case FIELD:
                    resourceType = ResourceType::Grain;
                    break;
                case PASTURE:
                    resourceType = ResourceType::Wool;
                    break;
                case MOUNTAIN:
                    resourceType = ResourceType::Ore;
                    break;
                default:
                    resourceType = ResourceType::Invalid;
                    break;
            }

            if (resourceType != ResourceType::Invalid) {
                auto it = std::find_if(players.begin(), players.end(), [&owner](Player* player) {
                    return player->getName() == owner;
                });
                if (it != players.end()) {
                    (*it)->modifyResource(resourceType, resources);
                }
            }
        }
    }
}

void buildIsland(vector<Tile*>& island) {
    // Clear the island vector in case it contains any previous tiles
    island.clear();

    // Ensure size is 5x5 for this specific board layout
    int size = 5;

    // Define a predefined layout for a 5x5 board
    LandType predefinedLandTypes[5][5] = {
        {FOREST, HILLS, FIELD, PASTURE, MOUNTAIN},
        {MOUNTAIN, FIELD, FOREST, HILLS, PASTURE},
        {PASTURE, MOUNTAIN, FIELD, FOREST, HILLS},
        {HILLS, PASTURE, MOUNTAIN, FIELD, FOREST},
        {FIELD, FOREST, HILLS, PASTURE, MOUNTAIN}
    };

    int predefinedNumbers[5][5] = {
        {5, 2, 6, 3, 8},
        {8, 10, 9, 12, 4},
        {11, 4, 8, 10, 5},
        {3, 9, 5, 6, 11},
        {2, 6, 3, 8, 10}
    };

    // Create the tiles based on the predefined layout
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            island.push_back(new EmptyTile(predefinedLandTypes[i][j], predefinedNumbers[i][j]));
        }
    }
}

void renderIsland(vector<Tile*> island) {
    int size = 5; // Always 5x5

    for (int s = 0; s < size; s++) {
        for (int i = 0; i <= 6; i++) {
            for (int j = size * s; j < (size * (s + 1)); j++) {
                cout << island.at(j)->render(i) << " ";
            }
            cout << endl;
        }
    }
}

void initializePlayers(vector<Player*> &players) {
    string name;
    int playerCount = 3; // Always 3 players

    for (int i = 0; i < playerCount; i++) {
        cout << "\t\t\tWhat is Player " << (i + 1) << "'s name? ";
        cin >> name;
        players.push_back(new Player(name, 1, 1, 1, 1, 1, 0));
    }

    cout << endl << "\t             Welcome to the Island of Catan ";

    for (int i = 0; i < playerCount; i++) {
        if (i != 0) {
            if (i == playerCount - 1) {
                cout << " & ";
            } else {
                cout << ", ";
            }
        }
        cout << players.at(i)->getName();
    }

    cout << "." << endl;
}

void resources(vector<Player*>& players, int z) {
    cout << "    |~~~~~~~~~~~~~~~~ Victory Points: " << players.at(z)->getVictoryPoints() << " ~~~~~~~~~~~~~~~~|" << endl;
    cout << "    | Wood: " << players.at(z)->getResource(ResourceType::Wood);
    cout << "   Bricks: " << players.at(z)->getResource(ResourceType::Brick);
    cout << "   Grain: " << players.at(z)->getResource(ResourceType::Grain);
    cout << "   Wool: " << players.at(z)->getResource(ResourceType::Wool);
    cout << "   Ore: " << players.at(z)->getResource(ResourceType::Ore) << "|" << endl << endl;
}

void buyRoad(vector<Player*>& players, vector<Tile*>& island, int player) {
    int fromRow, fromCol, toRow, toCol;
    int fromIndex, toIndex;
    int size = 5; // Always 5x5

    cout << "\t \tBUILDING A ROAD" << endl;

    cout << "\tEnter the coordinates of the starting tile (row and column):" << endl;
    cin >> fromRow >> fromCol;
    while (fromRow < 1 || fromRow > size || fromCol < 1 || fromCol > size) {
        cout << "\t \tError: Coordinates are out of range." << endl;
        cin >> fromRow >> fromCol;
    }
    fromIndex = (size * (fromRow - 1)) + (fromCol - 1);

    cout << "\tEnter the coordinates of the ending tile (row and column):" << endl;
    cin >> toRow >> toCol;
    while (toRow < 1 || toRow > size || toCol < 1 || toCol > size) {
        cout << "\t \tError: Coordinates are out of range." << endl;
        cin >> toRow >> toCol;
    }
    toIndex = (size * (toRow - 1)) + (toCol - 1);

    if (players[player]->getResource(ResourceType::Wood) < 1 || players[player]->getResource(ResourceType::Brick) < 1) {
        cout << "\tNot enough resources to build a road!" << endl;
        return;
    }

    string name = players[player]->getName();
    if (island[fromIndex]->addRoad(name, fromIndex, toIndex)) {
        players[player]->modifyResource(ResourceType::Wood, -1);
        players[player]->modifyResource(ResourceType::Brick, -1);
        cout << "\tRoad built successfully!" << endl;
    } else {
        cout << "\tFailed to build road. Road already exists or invalid coordinates." << endl;
    }

    renderIsland(island);
}

void buySettlement(vector<Player*>& players, vector<Tile*>& island, int player) {
    int row, column, index;
    int size = 5; // Always 5x5

    cout << "\t \tBUYING A SETTLEMENT" << endl;
    cout << "\tOn which row is the desired tile located?" << endl;
    cin >> row;
    while (row < 1 || row > size) {
        cout << "\t \tError: Row is out of range." << endl;
        cin >> row;
    }

    cout << "\tOn which column is the desired tile located?" << endl;
    cin >> column;
    while (column < 1 || column > size) {
        cout << "\t \tError: Column is out of range." << endl;
        cin >> column;
    }

    index = (size * (row - 1)) + (column - 1);

    if (!island.at(index)->getOwner().empty()) {
        cout << "\tThere is already a settlement on this tile. Please choose another tile." << endl;
        return buySettlement(players, island, player);
    }

    int land = island.at(index)->getLand();
    int value = island.at(index)->getNumber();
    bool validPlacement = false;

    // Check adjacent tiles for valid placement
    vector<int> adjacentIndices;
    if (row > 1) adjacentIndices.push_back(index - size);        // Tile above
    if (row < size) adjacentIndices.push_back(index + size);     // Tile below
    if (column > 1) adjacentIndices.push_back(index - 1);        // Tile left
    if (column < size) adjacentIndices.push_back(index + 1);     // Tile right

    for (int adjIndex : adjacentIndices) {
        if (island.at(adjIndex)->getOwner() == players.at(player)->getName()) {
            validPlacement = true;
            break;
        }
    }

    if (!validPlacement) {
        cout << "\tYou don't own a settlement on an adjacent tile. Please choose another tile." << endl;
        return buySettlement(players, island, player);
    }

    island.at(index) = new SettledTile((LandType)land, value, players.at(player)->getName());
    players.at(player)->modifyResource(ResourceType::Wood, -1);
    players.at(player)->modifyResource(ResourceType::Brick, -1);
    players.at(player)->modifyResource(ResourceType::Grain, -1);
    players.at(player)->modifyResource(ResourceType::Wool, -1);
    players.at(player)->modifyVictoryPoints(1);

    renderIsland(island);
    takeTurn(players, island, player);
}

void buyDevelopmentCard(vector<Player*>& players, int player) {
    // Randomly choose a card type
    CardType cardType = static_cast<CardType>(rand() % 5);
    Card* newCard = nullptr;

    // Deduct resources
    players[player]->modifyResource(ResourceType::Ore, -1);
    players[player]->modifyResource(ResourceType::Grain, -1);
    players[player]->modifyResource(ResourceType::Wool, -1);

    // Add the new card to the player's development cards
    players[player]->addDevelopmentCard(newCard);

    std::cout << players[player]->getName() << " drew a ";

    switch (cardType) {
        case CardType::Knight:
            std::cout << "Knight card." << std::endl;
            break;
        case CardType::VictoryPoint:
            std::cout << "Victory Point card!" << std::endl;
            players[player]->modifyVictoryPoints(1);
            break;
        case CardType::RoadBuilding:
            std::cout << "Road Building card." << std::endl;
            break;
        case CardType::YearOfPlenty:
            std::cout << "Year of Plenty card." << std::endl;
            break;
        case CardType::Monopoly:
            std::cout << "Monopoly card." << std::endl;
            break;
    }
}

void buyCity(vector<Player*>& players, vector<Tile*>& island, int player) {
    int row, column;
    int index;
    int size = 5; // Always 5x5

    // Prompt player for the row of the desired tile
    cout << "\t \t!!!!!!BUYING A CITY!!!!!" << endl;
    cout << "\tOn which row is the desired tile located?" << endl;
    for(int i = 1; i <= size; i++) {
        cout << "\t[" << i << "]" << endl;
    }
    cin >> row;

    // Validate row input
    while(row < 1 || row > size) {
        cout << "\t!!!!!!Error: Row is out of range.!!!!!" << endl;
        cout << "\tOn which row is the desired tile located?" << endl;
        for(int i = 1; i <= size; i++) {
            cout << "\t[" << i << "]" << endl;
        }
        cin >> row;
    }

    // Prompt player for the column of the desired tile
    cout << "\tOn which column is the desired tile located?" << endl;
    for(int i = 1; i <= size; i++) {
        cout << "\t[" << i << "] ";
    }
    cout << endl;
    cin >> column;

    // Validate column input
    while(column < 1 || column > size) {
        cout << "\tError: Column is out of range." << endl;
        cout << "\tOn which column is the desired tile located?" << endl;
        for(int i = 1; i <= size; i++) {
            cout << "\t[" << i << "] ";
        }
        cout << endl;
        cin >> column;
    }

    // Calculate the index of the tile in the island vector
    index = (size * (row - 1)) + (column - 1);

    // Check if the player owns the settlement on the selected tile
    if(island.at(index)->getOwner() == players.at(player)->getName()) {
        int land = island.at(index)->getLand();
        int value = island.at(index)->getNumber();
        string owner = island.at(index)->getOwner();
        owner = owner + " (City)"; // Update the owner value to signify a city

        // Upgrade the settlement to a city
        island.at(index) = new CityTile((LandType)land, value, owner);
        players.at(player)->modifyResource(ResourceType::Ore, -3); // Deduct 3 ore
        players.at(player)->modifyResource(ResourceType::Grain, -2); // Deduct 2 grain
        players.at(player)->modifyVictoryPoints(1); // Increase victory points by 1
        renderIsland(island); // Render the updated island
        takeTurn(players, island, player); // Continue the player's turn

    // If the player already owns a city on the selected tile
    } else if(island.at(index)->getOwner() == players.at(player)->getName() + " (City)") {
        cout << "\tYou already own a city here." << endl;
        buyCity(players, island, player); // Prompt to choose another tile

    // If the player does not own a settlement on the selected tile
    } else {
        cout << endl << "\tYou do not own a settlement here." << endl;
        cout << "\t \tPlease choose another tile." << endl << endl;
        buyCity(players, island, player); // Prompt to choose another tile
    }
}

void buyPrompt(vector<Player*>& players, vector<Tile*>& island, int player) {
    while (choice != 5) {  // Loop until the player chooses to go back
        // Display the purchase options
        cout << "\t|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|" << endl;
        cout << "\t|1: Settlement (1 wood, 1 brick, 1 grain, 1 wool)|" << endl;
        cout << "\t|            2: City (3 ore, 2 grain)            |" << endl;
        cout << "\t|  3: Development Card (1 ore, 1 grain, 1 wool)  |" << endl;
        cout << "\t|            4: Road (1 wood, 1 brick)           |" << endl;
        cout << "\t|                    5: Back                     |" << endl;
        cout << "\t|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|" << endl;
        cin >> choice;

        // Validate the player's choice
        while (choice < 1 || choice > 5) {
            cout << "\t|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|" << endl;
            cout << "\t|1: Settlement (1 wood, 1 brick, 1 grain, 1 wool)|" << endl;
            cout << "\t|            2: City (3 ore, 2 grain)            |" << endl;
            cout << "\t|  3: Development Card (1 ore, 1 grain, 1 wool)  |" << endl;
            cout << "\t|            4: Road (1 wood, 1 brick)           |" << endl;
            cout << "\t|                    5: Back                     |" << endl;
            cout << "\t|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|" << endl;
            cin >> choice;
        }

        // Process the player's choice
        if (choice == 1) {  // Buy a Settlement
            if (players.at(player)->getResource(ResourceType::Wood) >= 1 && 
                players.at(player)->getResource(ResourceType::Brick) >= 1 && 
                players.at(player)->getResource(ResourceType::Grain) >= 1 && 
                players.at(player)->getResource(ResourceType::Wool) >= 1) {
                buySettlement(players, island, player);
            } else {
                cout << "\tYou do not have enough resources to build a settlement!" << endl;
                takeTurn(players, island, player);
            }
        } else if (choice == 2) {  // Buy a City
            if (players.at(player)->getResource(ResourceType::Ore) >= 3 && 
                players.at(player)->getResource(ResourceType::Grain) >= 2) {
                buyCity(players, island, player);
            } else {
                cout << "\t\tYou do not have enough resources to build a city!" << endl;
                takeTurn(players, island, player);
            }
        } else if (choice == 3) {  // Buy a Development Card
            if (players.at(player)->getResource(ResourceType::Ore) >= 1 && 
                players.at(player)->getResource(ResourceType::Grain) >= 1 && 
                players.at(player)->getResource(ResourceType::Wool) >= 1) {
                buyDevelopmentCard(players, player);
            } else {
                cout << "\tYou do not have enough resources to buy a development card!" << endl;
                takeTurn(players, island, player);
            }
        } else if (choice == 4) {  // Build a Road
            buyRoad(players, island, player);
        } else {  // Back
            takeTurn(players, island, player);
        }
    }
}

void tradePrompt(vector<Player*>& players, int player) {
    int playerChoice = selectTradePartner(players, player);
    if (playerChoice == -1) return;

    ResourceType giveRsrc = selectResource("give");
    if (giveRsrc == ResourceType::Invalid) return;

    int giveAmt = selectAmount("give", players, player, giveRsrc);
    if (giveAmt == -1) return;

    ResourceType recRsrc = selectResource("receive");
    if (recRsrc == ResourceType::Invalid) return;

    int recAmt = selectAmount("receive", players, playerChoice - 1, recRsrc);
    if (recAmt == -1) return;

    if (confirmTrade(players, player, playerChoice, giveRsrc, giveAmt, recRsrc, recAmt)) {
        executeTrade(players, player, playerChoice - 1, giveRsrc, giveAmt, recRsrc, recAmt);
    }
}

int selectTradePartner(std::vector<Player*>& players, int player) {
    int playerChoice;
    do {
        cout << "\t\tWho would you like to trade with?" << endl;
        for (size_t i = 0; i < players.size(); i++) { // Use size_t here
            if(static_cast<int>(i) != player) { // Cast i to int for comparison
                cout << i + 1 << ": " << players.at(i)->getName() << endl;
            }
        }
        cin >> playerChoice;

        if(playerChoice < 1 || static_cast<size_t>(playerChoice) > players.size() || playerChoice == (player + 1)) {
            cout << "\t!!!!!INVALID PLAYER SELECTION!!!!!" << endl;
        } else {
            return playerChoice;
        }
    } while(true);
}

ResourceType selectResource(const string& action) {
    int choice;
    cout << "\t|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|" << endl;
    cout << "\t|Which resource would you like to " << action << "?" << endl;
    cout << "\t|                 1: Wood                  |" << endl;
    cout << "\t|                 2: Brick                 |" << endl;
    cout << "\t|                 3: Grain                 |" << endl;
    cout << "\t|                 4: Wool                  |" << endl;
    cout << "\t|                 5: Ore                   |" << endl;
    cout << "\t|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|" << endl;
    cin >> choice;

    switch (choice) {
        case 1: return ResourceType::Wood;
        case 2: return ResourceType::Brick;
        case 3: return ResourceType::Grain;
        case 4: return ResourceType::Wool;
        case 5: return ResourceType::Ore;
        default: return ResourceType::Invalid;
    }
}

int selectAmount(const string& action, vector<Player*>& players, int player, ResourceType rsrc) {
    int amt;
    do {
        cout << "\tHow many are you willing to " << action << "? (1-5)" << endl;
        cin >> amt;

        if (players.at(player)->getResource(rsrc) < amt) {
            cout << "\tYou don't have enough resources for that trade. Try again." << endl;
        } else {
            return amt;
        }
    } while(true);
}

bool confirmTrade(vector<Player*>& players, int player, int playerChoice, ResourceType giveRsrc, int giveAmt, ResourceType recRsrc, int recAmt) {
    char response;
    cout << players.at(playerChoice - 1)->getName() << ", " << players.at(player)->getName() << " wants " << recAmt 
         << " of your " << getResourceName(recRsrc) << " in exchange for " << giveAmt << " of their " << getResourceName(giveRsrc) 
         << ". Do you accept? (y/n)" << endl;
    cin >> response;
    return response == 'Y' || response == 'y';
}

std::string getResourceName(ResourceType rsrc) {
    switch (rsrc) {
        case ResourceType::Wood: return "Wood";
        case ResourceType::Brick: return "Brick";
        case ResourceType::Grain: return "Grain";
        case ResourceType::Wool: return "Wool";
        case ResourceType::Ore: return "Ore";
        default: return "Unknown";
    }
}

void executeTrade(vector<Player*>& players, int player, int playerChoice, ResourceType giveRsrc, int giveAmt, ResourceType recRsrc, int recAmt) {
    players.at(player)->modifyResource(giveRsrc, -giveAmt);
    players.at(player)->modifyResource(recRsrc, recAmt);
    players.at(playerChoice)->modifyResource(giveRsrc, giveAmt);
    players.at(playerChoice)->modifyResource(recRsrc, -recAmt);

    cout << endl << players.at(player)->getName() << " now has ";
    resources(players, player);
    cout << endl;
    cout << players.at(playerChoice)->getName() << " now has ";
    resources(players, playerChoice);
    cout << endl;
}

void swapResources(vector<Player*>& players, int player) {
    if (!hasSufficientResources(players, player)) {
        cout << "\t!You need at least three of one resource to swap!" << endl << endl;
        return;
    }

    ResourceType swpRsrc = selectResource("trade in");
    if (swpRsrc == ResourceType::Invalid) {
        cout << "\t\tInvalid response." << endl;
        swapResources(players, player);
        return;
    }

    if (players[player]->getResource(swpRsrc) < 3) {
        cout << "\t!You do not have enough of that resource to swap!" << endl << endl;
        swapResources(players, player);
        return;
    }

    players[player]->modifyResource(swpRsrc, -3);

    ResourceType recRsrc = selectResource("receive");
    if (recRsrc == ResourceType::Invalid) {
        cout << "\t\tInvalid response!" << endl;
        swapResources(players, player);
        return;
    }

    players[player]->modifyResource(recRsrc, 1);
}

bool hasSufficientResources(vector<Player*>& players, int player) {
    return players[player]->getResource(ResourceType::Wood) >= 3 ||
           players[player]->getResource(ResourceType::Brick) >= 3 ||
           players[player]->getResource(ResourceType::Grain) >= 3 ||
           players[player]->getResource(ResourceType::Wool) >= 3 ||
           players[player]->getResource(ResourceType::Ore) >= 3;
}

int takeTurn(vector<Player*>& players, vector<Tile*>& island, int player) {
    while(players.at(player)->getVictoryPoints() < 10) {
        cout << players.at(player)->getName() << "'s turn." << endl << endl;
        resources(players, player);

        cout << "\t|!!!!!!!!!!!!!!!!!!!!!!!!!!|" << endl;
        cout << "\t|What would you like to do?|" << endl;
        cout << "\t|         1: Buy           |" << endl;
        cout << "\t|         2: Trade         |" << endl;
        cout << "\t|         3: Swap          |" << endl;
        cout << "\t|        4: End Turn       |" << endl;
        cout << "\t|!!!!!!!!!!!!!!!!!!!!!!!!!!|" << endl;
        cin >> choice;

        while (choice < 1 || choice > 4) {
            cout << "\t|!!!!!!!!!!!!!!!!|" << endl;
            cout << "\t|!INVALID CHOICE!|" << endl;
            cout << "\t|    1: Buy      |" << endl;
            cout << "\t|    2: Trade    |" << endl;
            cout << "\t|    3: Swap     |" << endl;
            cout << "\t|   4: End Turn  |" << endl;
            cout << "\t|!!!!!!!!!!!!!!!!|" << endl;
            cin >> choice;
        }

        if (choice == 1) {
            choice = 0;
            buyPrompt(players, island, player);
        } else if (choice == 2) {
            choice = 0;
            tradePrompt(players, player);
        } else if (choice == 3) {
            choice = 0;
            swapResources(players, player);
        } else {
            choice = 0;
            player++;
            if(static_cast<size_t>(player) >= players.size()) {
                player = 0;
            }
            renderIsland(island);
            diceRoll(players, island);
            takeTurn(players, island, player);
        }
    }
    return player;
}

void buildTwoRoads(Player& player, vector<Tile*>& island) {
    int fromRow, fromCol, toRow, toCol;
    int fromIndex, toIndex;
    int size = 5; // Assuming a 5x5 board

    for (int i = 0; i < 2; ++i) {
        std::cout << "Building road " << (i + 1) << " out of 2." << std::endl;

        std::cout << "\tEnter the coordinates of the starting tile (row and column):" << std::endl;
        std::cin >> fromRow >> fromCol;
        while (fromRow < 1 || fromRow > size || fromCol < 1 || fromCol > size) {
            std::cout << "\t \tError: Coordinates are out of range." << std::endl;
            std::cin >> fromRow >> fromCol;
        }
        fromIndex = (size * (fromRow - 1)) + (fromCol - 1);

        std::cout << "\tEnter the coordinates of the ending tile (row and column):" << std::endl;
        std::cin >> toRow >> toCol;
        while (toRow < 1 || toRow > size || toCol < 1 || toCol > size) {
            std::cout << "\t \tError: Coordinates are out of range." << std::endl;
            std::cin >> toRow >> toCol;
        }
        toIndex = (size * (toRow - 1)) + (toCol - 1);

        string name = player.getName();
        if (island[fromIndex]->addRoad(name, fromIndex, toIndex)) {
            std::cout << "\tRoad built successfully!" << std::endl;
        } else {
            std::cout << "\tFailed to build road. Road already exists or invalid coordinates." << std::endl;
            --i;  // Retry the current road
        }
    }
    renderIsland(island);  // Assuming `renderIsland` is a global function
}

void takeTwoResources(Player& player) {
    for (int i = 0; i < 2; ++i) {
        int choice;
        std::cout << "\t|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|" << std::endl;
        std::cout << "\t|Which resource would you like to take from the bank?|" << std::endl;
        std::cout << "\t|                 1: Wood                  |" << std::endl;
        std::cout << "\t|                 2: Brick                 |" << std::endl;
        std::cout << "\t|                 3: Grain                 |" << std::endl;
        std::cout << "\t|                 4: Wool                  |" << std::endl;
        std::cout << "\t|                 5: Ore                   |" << std::endl;
        std::cout << "\t|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|" << std::endl;
        std::cin >> choice;

        ResourceType resource;
        switch (choice) {
            case 1: resource = ResourceType::Wood; break;
            case 2: resource = ResourceType::Brick; break;
            case 3: resource = ResourceType::Grain; break;
            case 4: resource = ResourceType::Wool; break;
            case 5: resource = ResourceType::Ore; break;
            default: resource = ResourceType::Invalid; break;
        }

        if (resource != ResourceType::Invalid) {
            player.modifyResource(resource, 1);
            std::cout << player.getName() << " took 1 " << getResourceName(resource) << " from the bank." << std::endl;
        } else {
            std::cout << "Invalid choice. Try again." << std::endl;
            --i;  // Retry the current resource
        }
    }
}

void takeAllResourcesOfOneType(Player& player, vector<Player*>& players) {
    int choice;
    std::cout << "\t|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|" << std::endl;
    std::cout << "\t|Which resource would you like to take from other players?|" << std::endl;
    std::cout << "\t|                 1: Wood                  |" << std::endl;
    std::cout << "\t|                 2: Brick                 |" << std::endl;
    std::cout << "\t|                 3: Grain                 |" << std::endl;
    std::cout << "\t|                 4: Wool                  |" << std::endl;
    std::cout << "\t|                 5: Ore                   |" << std::endl;
    std::cout << "\t|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|" << std::endl;
    std::cin >> choice;

    ResourceType resource;
    switch (choice) {
        case 1: resource = ResourceType::Wood; break;
        case 2: resource = ResourceType::Brick; break;
        case 3: resource = ResourceType::Grain; break;
        case 4: resource = ResourceType::Wool; break;
        case 5: resource = ResourceType::Ore; break;
        default: resource = ResourceType::Invalid; break;
    }

    if (resource != ResourceType::Invalid) {
        int totalResources = 0;
        for (Player* p : players) {
            if (p != &player) {
                totalResources += p->getResource(resource);
                p->modifyResource(resource, -p->getResource(resource));
            }
        }
        player.modifyResource(resource, totalResources);
        std::cout << player.getName() << " took " << totalResources << " " << getResourceName(resource) << " from other players." << std::endl;
    } else {
        std::cout << "Invalid choice. Try again." << std::endl;
        takeAllResourcesOfOneType(player, players);  // Retry
    }
}







