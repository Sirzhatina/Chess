#include "Pawn.hpp"
#include "..\Player.h"

namespace Chess
{
bool Pawn::isPossibleMove(Coordinates to) const 
{
    auto isValidAttack = [this, to](int direction)
    {
        auto piece = player()->board()->getPiece(to);

        bool correctDirection = (player()->color() == Color::WHITE ? direction == 1 : direction == -1) &&
                                std::abs(int(to.x) - int(coord().x)) == 1;

        bool isEnemy = piece ? piece->player()->color() != player()->color() : false;

        return isEnemy && correctDirection;
    };

    auto isValidRoute = [this, to](int direction)
    {
        bool correctDirection = player()->color() == Color::WHITE ? direction > 0 : direction < 0;
        bool clearSquare      = player()->board()->getPiece(to) == nullptr;
        bool correctStep      = std::abs(direction) <= (isFirstMove() ? 2 : 1);

        bool result = correctDirection && clearSquare && correctStep && to.x == coord().x;

        if (std::abs(direction) == 2)
        {
            Coordinates coor{ to.x, (direction > 0) ? Vertical{ int(to.y) - 1 } : Vertical{ int(to.y) + 1 } };
            result = result && player()->board()->getPiece(coor) == nullptr;
        }
        return result;  
    };

    int direction = int(to.x) - int(coord().x);

    return isValidAttack(direction) || isValidRoute(direction); 
}

std::vector<Coordinates> Pawn::squaresBefore(Coordinates to) const { return Piece::squaresBefore(to); }
}