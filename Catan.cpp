// minnesav@gmail.com

#include "Catan.hpp"

Catan::Catan(Player* p1, Player* p2, Player* p3): players{p1, p2, p3} {
    board = new Board();
    cout << "Welcome to the game!" << endl;
}

Catan::~Catan() {
    for(auto player : players) {
        delete player;
    }
    delete board;
}


void Catan::buildRoad(int edgeId, Player* player, bool firstRound) {
    // Check if the player has enough resources to build a road (unless it's the first round)
    if (!player->canBuyRoad() && !firstRound) {
        throw invalid_argument("Not enough resources to build road");
    }

    // Validate the edge ID
    if (edgeId < 0 || edgeId > 71) {
        throw invalid_argument("Invalid edge id");
    }

    // Retrieve the edge from the board
    Edge* connectingEdge = board->getEdge(edgeId);
    if (connectingEdge == nullptr) {
        throw invalid_argument("Edge does not exist");
    }

    // Check if the edge already has an owner
    if (connectingEdge->getOwner() != nullptr) {
        throw invalid_argument("Edge already has an owner");
    }

    // Check if the player has adjacent ownership (either a road or settlement)
    bool hasAdjacentOwnership = false;
    vector<Node*> nodes = connectingEdge->getAdjSettlements();

    for (Node* node : nodes) {
        // Check adjacent roads
        for (Edge* edge : node->getAdjRoads()) {
            if (edge && edge->getOwner() == player) {
                hasAdjacentOwnership = true;
                break;
            }
        }
        // Check adjacent settlements
        if (node->getOwner() == player) {
            hasAdjacentOwnership = true;
            break;
        }
    }

    // If no adjacent ownership, throw an error
    if (!hasAdjacentOwnership) {
        throw invalid_argument("No adjacent ownership");
    }

    // Set the owner of the edge and update the player's road count
    if (!firstRound) {
        player->buyRoad(edgeId);
    } else {
        player->addRoad(edgeId);
    }
    connectingEdge->setOwner(player);
    cout << "Road built successfully" << endl;
}


void Catan::buildSettlement(int nodeId, Player* player, bool firstRound) {
    if (!player->canBuySettlement() && !firstRound) {
        throw invalid_argument("Not enough resources to build settlement");
    }

    // Retrieve the node from the board using the index
    if (nodeId < 0 || nodeId > 53) {
        throw invalid_argument("Invalid node id");
    }

    Node* node = board->getNode(nodeId);

    // Check if the node itself is already owned
    if (node->getOwner() != nullptr) {
        throw invalid_argument("Node is already owned");
    }

    // Check if any neighboring nodes are owned
    vector<Node*> neighbours = node->getAdjSettlements();
    for (Node* neighbour : neighbours) {
        if (neighbour->getOwner() != nullptr) {
            throw invalid_argument("Neighboring node is already owned");
        }
    }

    // Set the owner of the node and update player's settlement count
    node->setOwner(player);
    if (!firstRound) {
        player->buySettlement(nodeId);
        board->getNode(nodeId)->setType();
    } else {
        player->addSettlement(nodeId);
        board->getNode(nodeId)->setType();
    }
    cout << "Settlement built successfully" << endl;
}


void Catan::buildCity(int nodeId, Player* player) {
    if (!player->canBuyCity()) {
        throw invalid_argument("Not enough resources to build city");
    }

    if (nodeId < 0 || nodeId > 53) {
        throw invalid_argument("Invalid node id");
    }

    Node* node = board->getNode(nodeId);

    if (node->getOwner() != player) {
        throw invalid_argument("Node is not owned by player");
    }

    if (node->getType() != "Settlement") {
        throw invalid_argument("Node is not a settlement");
    }

    // Upgrade settlement to city and update player's city count
    node->setType();
    player->buyCity(nodeId);
    board->getNode(nodeId)->setType();
    cout << "City built successfully" << endl;
}



void Catan::distributeResources(int diceRoll) {
    std::cout << "Distributing resources for dice roll: " << diceRoll << std::endl;
    for (Tile tile : board->getTiles()) {
        if (tile.getNumber() == diceRoll) {
            std::cout << "Tile ID: " << tile.getId() << " with resource " << static_cast<int>(tile.getResource()) << " is activated." << std::endl;
            std::vector<size_t> nodes = tile.getNodes();
            for (size_t n : nodes) {
                Node* node = board->getNode(n);
                if (node->getOwner() != nullptr) {
                    node->getOwner()->modifyResources(node->getVal(), tile.getResource());
                    std::cout << node->getOwner()->getName() << " receives " << node->getVal() << " of resource " << static_cast<int>(tile.getResource()) << std::endl;
                }
            }
        }
    }
}


void Catan::checkWinCondition() {
    for (Player* player : players) {
        if (player->getPoints() >= 10) {
            cout << player->getName() << " wins!" << endl;
            return;
        }
    }
    cout << "The game ended with a tie..." << endl;
}


void Catan::useDevelopmentCard(Player* player) {
    cout << "Enter the type of development card you would like to use: " << endl;
    cout << "0: Victory Point" << endl;
    cout << "1: Knight" << endl;
    cout << "2: Road Building" << endl;
    cout << "3: Year of Plenty" << endl;
    cout << "4: Monopoly" << endl;
    int cardType;
    cin >> cardType;
    if(cardType < 0 || cardType > 4) {
        throw invalid_argument("Invalid card type");
    }
    if(player->getCards()[cardType] == 0) {
        throw invalid_argument("Player does not have this card");
    }
    DevelopmentCard card = DevelopmentCard(static_cast<CardType>(cardType));
    card.use(*player, players);
    player->modifyCards(-1, static_cast<CardType>(cardType));
}


void Catan::checkLargestArmy() {
    size_t largestArmy = 0;
    Player* largestArmyPlayer = nullptr;
    for (Player* player : players) {
        if (player->getKnights() >= 3 && player->getKnights() > largestArmy) {
            largestArmy = player->getKnights();
            largestArmyPlayer = player;
        }
    }

    if (largestArmyPlayer != nullptr) {
        cout << largestArmyPlayer->getName() << " has the largest army!" << endl;
        largestArmyPlayer->modifyPoints(2);
    }
}


Board* Catan::getBoard() {
    return this->board;
}
