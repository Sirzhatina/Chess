#include "Knight.hpp"
#include "..\Player.h"

namespace Chess
{
bool Knight::isPossibleMove(Coordinates to) const 
{
    auto isValidRoute = [this](Coordinates to)
    {
        if ((std::abs(int(to.y) - int(coord().y)) == 2 && std::abs(int(to.x) - int(coord().x)) == 1) ||
            (std::abs(int(to.x) - int(coord().x)) == 2 && std::abs(int(to.y) - int(coord().y)) == 1))
        {
            return true;
        }
        return false;
    };

    return !isFriendlySquare(to) && isValidRoute(to);
}

std::vector<Coordinates> Knight::squaresBefore(Coordinates to) const { return Piece::squaresBefore(to); }
}
