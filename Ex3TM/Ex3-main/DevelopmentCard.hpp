// minnesav@gmail.com

#ifndef DEVELOPMENTCARD_HPP
#define DEVELOPMENTCARD_HPP

#include <string>
#include "Player.hpp"
#include "Tile.hpp"

namespace Game {

    std::string resourceToString(Resource resource);

    class Player;

        class DevelopmentCard {
        public:
            virtual void use(Game::Player &player) = 0;

            virtual ~DevelopmentCard() {}
        };

        class KnightCard : public DevelopmentCard {
        public:
            void use(Player &player) override;
        };

        class MonopolyCard : public DevelopmentCard { 
        public:
            void use(Player &player) override;
        };

        class RoadBuildingCard : public DevelopmentCard {
        public:
            void use(Player &player) override;
        };

        class YearOfPlentyCard : public DevelopmentCard {
        public:
            void use(Player &player) override;
        };

        class VictoryPointCard : public DevelopmentCard {
        public:
            void use(Player &player) override;
        };
    }



#endif // DEVELOPMENTCARD_HPP
