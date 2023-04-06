module King;

import Queen;

namespace Core
{

bool King::isPossibleMove(Coordinates to) const 
{ 
    auto isValidRoute = [this, to]()
    {
        if (std::abs(int(to.x) - int(coord().x)) > 1 || std::abs(int(to.y) - int(coord().y)) > 1)
        {
            return false;
        }
        return !isSameSquare(to) && !isFriendlySquare(to);
    };
    return isValidRoute(); 
}

bool King::isAbleToMove() const
{
    return Queen{player(), coord()}.isAbleToMove();
}

std::vector<Coordinates> King::squaresBefore(Coordinates to) const { return Piece::squaresBefore(to); }
}
