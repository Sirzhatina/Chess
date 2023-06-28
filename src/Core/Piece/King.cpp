#include "King.hpp"
#include "../Player.hpp"
#include "Bishop.hpp"
#include "Rook.hpp"

namespace Chess
{

bool King::isValidRoute(Coordinates to) const
{
    if (std::abs(int(to.x) - int(coord().x)) > 1 || std::abs(int(to.y) - int(coord().y)) > 1)
    {
        return false;
    }
    return Piece::isValidRoute(to);
}

bool King::isClearRoute(Coordinates to) const
{
    return true;
}


bool King::isAbleToMove() const
{
    return Queen{player(), coord()}.isAbleToMove();
}
}
