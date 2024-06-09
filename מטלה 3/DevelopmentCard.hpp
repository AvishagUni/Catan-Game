// minnesav@gmail.com

#ifndef DEVELOPMENTCARD_HPP
#define DEVELOPMENTCARD_HPP

#include "Player.hpp"
#include "Resource.hpp"

namespace Game {
    class Player;

    namespace DevelopmentCards {
        class DevelopmentCard {
        public:
            virtual void use(Player &player) = 0;

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
    }

}

#endif // DEVELOPMENTCARD_HPP
