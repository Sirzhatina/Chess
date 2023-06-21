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
    return !isSameSquare(to) && !isFriendlySquare(to);    
}

bool King::isClearRoute(Coordinates to) const
{
    return true;
}


bool King::isAbleToMove() const
{
    return Bishop{player(), coord()}.isAbleToMove() || Rook{player(), coord()}.isAbleToMove();
}

std::vector<Coordinates> King::squaresBefore(Coordinates to) const { return Piece::squaresBefore(to); }
}
