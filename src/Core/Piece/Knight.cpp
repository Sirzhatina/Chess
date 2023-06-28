#include "Knight.hpp"
#include "..\Player.hpp"

namespace Chess
{

bool Knight::isValidRoute(Coordinates to) const
{
        if ((std::abs(int(to.y) - int(coord().y)) == 2 && std::abs(int(to.x) - int(coord().x)) == 1) ||
            (std::abs(int(to.x) - int(coord().x)) == 2 && std::abs(int(to.y) - int(coord().y)) == 1))
        {
            return Piece::isValidRoute(to);
        }
        return false;
}

bool Knight::isClearRoute(Coordinates to) const
{
    return true;
}

bool Knight::isAbleToMove() const
{
    /*
                 (-1, 2)      (1, 2)
        (-2, 1)                       (2, 1)
                           N
        (-2, -1)                      (2, -1)
                 (-1, -2)     (1, -2)
    */

    bool result = isAbleToSqr(coord(), 1, 2)   || isAbleToSqr(coord(), 2, 1)   ||
                  isAbleToSqr(coord(), 2, -1)  || isAbleToSqr(coord(), 1, -2)  ||
                  isAbleToSqr(coord(), -1, -2) || isAbleToSqr(coord(), -2, -1) ||
                  isAbleToSqr(coord(), -2, 1)  || isAbleToSqr(coord(), -1, 2);
    return result;
}
}
