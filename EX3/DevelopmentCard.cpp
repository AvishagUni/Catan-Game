#include "DevelopmentCard.hpp"

namespace ariel
{
    DevelopmentCard::DevelopmentCard(CardType type) : type(type) {}

    CardType DevelopmentCard::getType() const
    {
        return type;
    }

    std::string DevelopmentCard::getTypeName() const
    {
        switch (type)
        {
        case CardType::KNIGHT:
            return "Knight";
        case CardType::VICTORY_POINT:
            return "Victory Point";
        case CardType::ROAD_BUILDING:
            return "Road Building";
        case CardType::YEAR_OF_PLENTY:
            return "Year of Plenty";
        case CardType::MONOPOLY:
            return "Monopoly";
        default:
            return "Unknown";
        }
    }
}
