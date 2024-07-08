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
    if (!player->canBuyRoad() && !firstRound) {
        throw invalid_argument("Not enough resources to build road");
    }
    if (edgeId < 0 || edgeId > 71) {
        throw invalid_argument("Invalid edge id");
    }

    Edge* connectingEdge = board->getEdge(edgeId);
    if (connectingEdge == nullptr) {
        throw invalid_argument("Edge does not exist");
    }

    if (connectingEdge->getOwner() != nullptr) {
        throw invalid_argument("Edge already has an owner");
    }

    bool hasAdjacentOwnership = false;
    vector<Node*> nodes = connectingEdge->getAdjSettlements();

    for (Node* node : nodes) {
        for (Edge* edge : node->getAdjRoads()) {
            if (edge && edge->getOwner() == player) {
                hasAdjacentOwnership = true;
                break;
            }
        }
        if (node->getOwner() == player) {
            hasAdjacentOwnership = true;
            break;
        }
    }

    if (!hasAdjacentOwnership) {
        throw invalid_argument("No adjacent ownership");
    }

    connectingEdge->setOwner(player);
    if(!firstRound) {
        player->buyRoad(edgeId);
    }
    player->addRoad(edgeId);
    cout << "Road built successfully" << endl;
}

void Catan::buildSettlement(int nodeId, Player* p, bool firstRound) {
    if(!p->canBuySettlement()&& !firstRound) {
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

    // Check if any neighbouring nodes are owned
    vector<Node*> neighbours = node->getAdjSettlements();
    for (Node* neighbour : neighbours)
    {
        if (neighbour->getOwner() != nullptr)
        {
            throw invalid_argument("Neighbouring node is already owned");
        }
    }

    node->setOwner(p);
    if(!firstRound) {
    p->buySettlement(nodeId);
    board->getNode(nodeId)->setType();
    }
    p->addSettlement(nodeId);
    board->getNode(nodeId)->setType();
    cout << "Settlement built successfully" << endl;
}

void Catan::buildCity(int nodeId, Player* p) {
    if(!p->canBuyCity()) {
        throw invalid_argument("Not enough resources to build city");
    }

    if (nodeId < 0 || nodeId > 53) {
        throw invalid_argument("Invalid node id");
    }

    Node* node = board->getNode(nodeId);

    if (node->getOwner() != p) {
        throw invalid_argument("Node is not owned by player");
    }

    if (node->getType() != "Settlement") {
        throw invalid_argument("Node is not a settlement");
    }

    node->setType();
    p->buyCity(nodeId);
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
