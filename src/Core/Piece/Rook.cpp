#include "Rook.hpp"
#include "../Player.hpp"

namespace Chess
{

bool Rook::isValidRoute(Coordinates to) const
{
    bool horizontal = to.x != coord().x;
    bool vertical   = to.y != coord().y;

    return Piece::isValidRoute(to) && (horizontal ^ vertical);
}

bool Rook::isClearRoute(Coordinates to) const
{
    bool horizontal = to.x != coord().x;
    bool vertical   = to.y != coord().y;
    if (horizontal ^ vertical)
    {
        return false;
    }

    auto isClearSquare = [this](Coordinates c) { return player()->board()->getPiece(c) == nullptr; };

    Coordinates coor;
    int increment = 0;

    if (horizontal)
    {
        increment = (int(to.x) - int(coord().x) > 0) ? 1 : -1;
        coor = { Horizontal(int(coord().x) + increment), coord().y };
        
        while (coor != to)
        {
            if (!isClearSquare(coor))
            {
                return false;
            }
            coor.x = Horizontal(int(coor.x) + increment);
        }
    }
    else
    {
        increment = int(to.y) - int(coord().y) > 0 ? 1 : -1;
        coor = { coord().x, Vertical(int(coord().y) + increment) };
        while (coor != to)
        {
            if (!isClearSquare(coor))
            {
                return false;
            }
            coor.y = Vertical(int(coor.y) + increment);
        }
    }
    return true;
}

bool Rook::isAbleToMove() const
{
    /*
                (0, 1)
        (-1, 0)   R   (1, 0)
               (0, -1)
    */
    bool result = isAbleToMoveToSqr(coord(), 0, 1)  || 
                  isAbleToMoveToSqr(coord(), 1, 0)  ||
                  isAbleToMoveToSqr(coord(), 0, -1) || 
                  isAbleToMoveToSqr(coord(), -1, 0);
    return result;
}
}
