// minnesav@gmail.com

#ifndef PLAYERACTION_HPP
#define PLAYERACTION_HPP

#include "Player.hpp"
#include "Board.hpp"

namespace Game {
    class Player;
    class Board;

    namespace Actions {
        class PlayerAction {
        public:
            virtual void execute(Player& player, Board& board) = 0;
            virtual ~PlayerAction() {}
        };

        class BuildSettlementAction : public PlayerAction {
        public:
            void execute(Player& player, Board& board) override;
        };

        class BuildRoadAction : public PlayerAction {
        public:
            void execute(Player& player, Board& board) override;
        };

        class BuildCityAction : public PlayerAction {
        public:
            void execute(Player& player, Board& board) override;
        };

        class TradeWithPlayerAction : public PlayerAction {
        public:
            void execute(Player& player, Board& board) override;
        };

        class TradeWithBankAction : public PlayerAction {
        public:
            void execute(Player& player, Board& board) override;
        };

        class UseDevelopmentCardAction : public PlayerAction {
        public:
            void execute(Player& player, Board& board) override;
        };

        class EndTurnAction : public PlayerAction {
        public:
            void execute(Player& player, Board& board) override;
        };
    }
}

#endif // PLAYERACTION_HPP

