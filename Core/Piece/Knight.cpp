#include "Knight.hpp"
#include "..\Player.hpp"

namespace Chess
{
bool Knight::isPossibleMove(Coordinates to) const 
{
    auto isValidRoute = [this](Coordinates to)
    {
        if ((std::abs(int(to.y) - int(coord().y)) == 2 && std::abs(int(to.x) - int(coord().x)) == 1) ||
            (std::abs(int(to.x) - int(coord().x)) == 2 && std::abs(int(to.y) - int(coord().y)) == 1))
        {
            return !isFriendlySquare(to) && !isSameSquare(to);
        }
        return false;
    };

    return isValidRoute(to);
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

    auto src = coord();
    return src.tryShift(1, 2)   && isPossibleMove(src) || src.tryShift(2, 1)   && isPossibleMove(src) ||
           src.tryShift(2, -1)  && isPossibleMove(src) || src.tryShift(-2, 1)  && isPossibleMove(src) ||
           src.tryShift(-1, -2) && isPossibleMove(src) || src.tryShift(-2, -1) && isPossibleMove(src) ||
           src.tryShift(-2, 1)  && isPossibleMove(src) || src.tryShift(2, -1)  && isPossibleMove(src);
}

std::vector<Coordinates> Knight::squaresBefore(Coordinates to) const { return Piece::squaresBefore(to); }
}
