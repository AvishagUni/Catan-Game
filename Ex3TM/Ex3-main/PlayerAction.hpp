// minnesav@gmail.com

#ifndef PLAYERACTION_HPP
#define PLAYERACTION_HPP

#include "Player.hpp"
#include "Board.hpp"
#include <iostream>

namespace Game {

    class Board;
    class Player;

        class PlayerAction {
        public:
        virtual void execute(Player& player, Board& board) = 0;
        virtual ~PlayerAction() = default;
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


#endif // PLAYERACTION_HPP

