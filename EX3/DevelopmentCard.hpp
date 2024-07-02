#ifndef DEVELOPMENT_CARD_HPP
#define DEVELOPMENT_CARD_HPP

#include <string>

namespace ariel
{
    enum class CardType
    {
        KNIGHT,
        VICTORY_POINT,
        ROAD_BUILDING,
        YEAR_OF_PLENTY,
        MONOPOLY
    };

    class DevelopmentCard
    {
    private:
        CardType type;

    public:
        DevelopmentCard(CardType type);

        CardType getType() const;
        std::string getTypeName() const;
    };
}

#endif


