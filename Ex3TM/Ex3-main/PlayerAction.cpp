
// minnesav@gmail.com

#include "PlayerAction.hpp"

using namespace std;
using namespace Game;

void BuildSettlementAction::execute(Player& player, Board& board) {
    int vertexIndex;
    cout << "Player " << player.name << ", enter vertex index to build settlement: ";
    cin >> vertexIndex;
    if (vertexIndex >= 0 && vertexIndex < static_cast<int>(board.vertices.size())) {
        Vertex* vertex = &board.vertices[vertexIndex];
        if (player.placeSettlement(vertex)) {
            cout << "Settlement built successfully." << endl;
        } else {
            cout << "Cannot build settlement here." << endl;
        }
    } else {
        cout << "Invalid vertex index." << endl;
    }
}

void BuildRoadAction::execute(Player& player, Board& board) {
    int edgeIndex;
    cout << "Player " << player.name << ", enter edge index to build road: ";
    cin >> edgeIndex;
    if (edgeIndex >= 0 && edgeIndex < static_cast<int>(board.edges.size())) {
        Edge* edge = &board.edges[edgeIndex];
        if (player.placeRoad(edge)) {
            cout << "Road built successfully." << endl;
        } else {
            cout << "Cannot build road here." << endl;
        }
    } else {
        cout << "Invalid edge index." << endl;
    }
}

void BuildCityAction::execute(Player& player, Board& board) {
    int vertexIndex;
    cout << "Player " << player.name<< ", enter vertex index to build city: ";
    cin >> vertexIndex;
    if (vertexIndex >= 0 && vertexIndex < static_cast<int>(board.vertices.size())) {
        Vertex* vertex = &board.vertices[vertexIndex];
        if (player.placeCity(vertex)) {
            cout << "City built successfully." << endl;
        } else {
            cout << "Cannot build city here." << endl;
        }
    } else {
        cout << "Invalid vertex index." << endl;
    }
}

void TradeWithPlayerAction::execute(Player& player, Board& board) {
    int otherPlayerIndex;
    cout << "Player " << player.name << ", enter player index to trade with: ";
    cin >> otherPlayerIndex;
    if (otherPlayerIndex >= 0 && otherPlayerIndex < static_cast<int>(board.players.size())) {
        Player& otherPlayer = board.players[otherPlayerIndex];
        int giveResource, receiveResource, giveAmount, receiveAmount;

        cout << "Enter resource to give (0:WOOD, 1:BRICK, 2:WOOL, 3:OATS, 4:IRON): ";
        cin >> giveResource;
        cout << "Enter amount to give: ";
        cin >> giveAmount;
        cout << "Enter resource to receive (0:WOOD, 1:BRICK, 2:WOOL, 3:OATS, 4:IRON): ";
        cin >> receiveResource;
        cout << "Enter amount to receive: ";
        cin >> receiveAmount;

        if (player.trade(otherPlayer, static_cast<Resource>(giveResource), giveAmount, static_cast<Resource>(receiveResource), receiveAmount)) {
            cout << "Trade successful." << endl;
        } else {
            cout << "Trade failed. Check resource amounts." << endl;
        }
    } else {
        cout << "Invalid player index." << endl;
    }
}

void TradeWithBankAction::execute(Player& player, Board& board) {
    (void)board;  // Suppress unused parameter warning
    int giveResource, receiveResource, giveAmount;

    cout << "Player " << player.name << ", enter resource to give (0:WOOD, 1:BRICK, 2:WOOL, 3:OATS, 4:IRON): ";
    cin >> giveResource;
    cout << "Enter amount to give: ";
    cin >> giveAmount;
    cout << "Enter resource to receive (0:WOOD, 1:BRICK, 2:WOOL, 3:OATS, 4:IRON): ";
    cin >> receiveResource;

    player.tradeWithBank(static_cast<Resource>(giveResource), giveAmount, static_cast<Resource>(receiveResource));
}

void UseDevelopmentCardAction::execute(Player& player, Board& board) {
    (void)board;  // Suppress unused parameter warning
    int cardIndex;
    cout << "Player " << player.name<< ", enter development card index to use: ";
    cin >> cardIndex;
    player.useDevelopmentCard(cardIndex);
}

void EndTurnAction::execute(Player& player, Board& board) {
    (void)board;  // Suppress unused parameter warning
    cout << "Ending turn for Player " << player.name<< endl;
}

    



