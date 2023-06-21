#include "Bishop.hpp"
#include "../Player.hpp"

namespace Chess
{

bool Bishop::isValidRoute(Coordinates to) const
{
    int diffOnX = int(to.x) - int(coord().x);
    int diffOnY = int(to.y) - int(coord().y);

    bool isDiagonal = std::abs(diffOnX) == std::abs(diffOnY);

    return !isSameSquare(to) && !isFriendlySquare(to) && isDiagonal;
}

bool Bishop::isClearRoute(Coordinates to) const
{
    int incX = int(to.x) - int(coord().x) > 0 ? 1 : -1;
    int incY = int(to.y) - int(coord().y) > 0 ? 1 : -1;

    Coordinates start{Horizontal{int(coord().x) + incX}, Vertical{int(coord().y) + incY}};

    while (start != to)
    {
        if (player()->board()->getPiece(start) != nullptr)
        {
            return false;
        }
        start.x = Horizontal{int(start.x) + incX};
        start.y = Vertical{int(start.y) + incY};
    }
    return true;
}

bool Bishop::isAbleToMove() const
{
    /*
        (-1, 1)    (1, 1)
                 B
        (-1, -1)   (1, -1)
    */
    bool result = isAbleToSqr(coord(), 1, 1)   || isAbleToSqr(coord(), 1, -1) ||
                  isAbleToSqr(coord(), -1, -1) || isAbleToSqr(coord(), -1, 1);
    return result;
}

std::vector<Coordinates> Bishop::squaresBefore(Coordinates to) const
{
    int diffX = int(to.x) - int(coord().x);
    int diffY = int(to.y) - int(coord().y);

    std::vector<Coordinates> result{ coord() };

    if (std::abs(diffX) == std::abs(diffY))
    {
        int incX = (diffX > 0) ? 1 : -1;
        int incY = (diffY > 0) ? 1 : -1;

        auto coor = coord();
        coor.x = Horizontal(int(coor.x) + incX); 
        coor.y = Vertical(int(coor.y) + incY);
        while (coor != to)
        {
            result.push_back(coor);

            coor.x = Horizontal(int(coor.x) + incX); 
            coor.y = Vertical(int(coor.y) + incY);
        }
    }
    return result;
}
}
