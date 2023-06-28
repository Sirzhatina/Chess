#include "Pawn.hpp"
#include "..\Player.hpp"

namespace Chess
{
bool Pawn::isValidAttack(Coordinates to) const
{
    int direction = int(to.y) - int(coord().y);

    auto piece = player()->board()->getPiece(to);

    bool correctDirection = (player()->color() == Color::WHITE ? direction == 1 : direction == -1) &&
                            std::abs(int(to.x) - int(coord().x)) == 1;

    bool isEnemy = piece ? piece->player()->color() != player()->color() : false;

    return isEnemy && correctDirection;
}

bool Pawn::isValidRoute(Coordinates to) const
{
    int direction = int(to.y) - int(coord().y);

    bool correctDirection = (player()->color() == Color::WHITE ? direction > 0 : direction < 0);
    bool clearSquare      = player()->board()->getPiece(to) == nullptr;
    bool correctStep      = std::abs(direction) <= (isFirstMove() ? 2 : 1);

    bool result = correctDirection && clearSquare && correctStep && to.x == coord().x;

    if (std::abs(direction) == 2)
    {
        Coordinates coor{ to.x, (direction > 0) ? Vertical{ int(to.y) - 1 } : Vertical{ int(to.y) + 1 } };
        result = result && player()->board()->getPiece(coor) == nullptr;
    }
    return result || isValidAttack(to);  
}

bool Pawn::isClearRoute(Coordinates to) const
{
    return true;
}

bool Pawn::isAbleToMove() const
{
    int incY = (player()->color() == Color::WHITE ? 1 : -1);
    
    return isAbleToMoveToSqr(coord(), -1, incY) || isAbleToMoveToSqr(coord(), 0, incY) || isAbleToMoveToSqr(coord(), 1, incY);
}
}