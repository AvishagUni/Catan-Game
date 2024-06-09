// minnesav@gmail.com

#include "PlayerAction.hpp"

namespace Game {
    namespace Actions {
        void BuildSettlementAction::execute(Player& player, Board& board) {
            int vertexIndex;
            std::cout << "Enter vertex index to build settlement: ";
            std::cin >> vertexIndex;
            if (vertexIndex >= 0 && vertexIndex < board.vertices.size()) {
                player.buildSettlement(&board.vertices[vertexIndex]);
            } else {
                std::cout << "Invalid vertex index." << std::endl;
            }
        }

        void BuildRoadAction::execute(Player& player, Board& board) {
            int edgeIndex;
            std::cout << "Enter edge index to build road: ";
            std::cin >> edgeIndex;
            if (edgeIndex >= 0 && edgeIndex < board.edges.size()) {
                player.buildRoad(&board.edges[edgeIndex]);
            } else {
                std::cout << "Invalid edge index." << std::endl;
            }
        }

        void BuildCityAction::execute(Player& player, Board& board) {
            int vertexIndex;
            std::cout << "Enter vertex index to build city: ";
            std::cin >> vertexIndex;
            if (vertexIndex >= 0 && vertexIndex < board.vertices.size()) {
                player.buildCity(&board.vertices[vertexIndex]);
            } else {
                std::cout << "Invalid vertex index." << std::endl;
            }
        }

        void TradeWithPlayerAction::execute(Player& player, Board& board) {
            int otherPlayerIndex, giveResource, receiveResource, giveAmount, receiveAmount;
            std::cout << "Enter player index to trade with: ";
            std::cin >> otherPlayerIndex;
            std::cout << "Enter resource to give (0:WOOD, 1:BRICK, 2:WOOL, 3:OATS, 4:IRON): ";
            std::cin >> giveResource;
            std::cout << "Enter amount to give: ";
            std::cin >> giveAmount;
            std::cout << "Enter resource to receive (0:WOOD, 1:BRICK, 2:WOOL, 3:OATS, 4:IRON): ";
            std::cin >> receiveResource;
            std::cout << "Enter amount to receive: ";
            std::cin >> receiveAmount;

            if (otherPlayerIndex >= 0 && otherPlayerIndex < board.players.size()) {
                if (!player.trade(board.players[otherPlayerIndex], static_cast<Resource>(giveResource), giveAmount, static_cast<Resource>(receiveResource), receiveAmount)) {
                    std::cout << "Trade failed." << std::endl;
                }
            } else {
                std::cout << "Invalid player index." << std::endl;
            }
        }

        void TradeWithBankAction::execute(Player& player, Board& board) {
            int giveResource, receiveResource, giveAmount;
            std::cout << "Enter resource to give (0:WOOD, 1:BRICK, 2:WOOL, 3:OATS, 4:IRON): ";
            std::cin >> giveResource;
            std::cout << "Enter amount to give: ";
            std::cin >> giveAmount;
            std::cout << "Enter resource to receive (0:WOOD, 1:BRICK, 2:WOOL, 3:OATS, 4:IRON): ";
            std::cin >> receiveResource;

            player.tradeWithBank(static_cast<Resource>(giveResource), giveAmount, static_cast<Resource>(receiveResource));
        }

        void UseDevelopmentCardAction::execute(Player& player, Board& board) {
            int cardIndex;
            std::cout << "Enter development card index to use: ";
            std::cin >> cardIndex;
            player.useDevelopmentCard(cardIndex);
        }

        void EndTurnAction::execute(Player& player, Board& board) {
            std::cout << "Ending turn for Player " << player.playerID + 1 << std::endl;
        }
    }
}


