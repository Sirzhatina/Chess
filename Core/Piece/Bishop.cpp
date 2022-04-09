#include "Bishop.hpp"
#include "../Player.hpp"

namespace Chess
{
bool Bishop::isPossibleMove(Coordinates to) const 
{
    auto isValidRoute = [this, to](int differenceOnX, int differenceOnY)
    {
        bool isDiagonal = std::abs(differenceOnX) == std::abs(differenceOnY);
        return !isSameSquare(to) && !isFriendlySquare(to) && isDiagonal;
    };

    auto isClearRoute = [this, to](int incX, int incY, Coordinates each)
    {
        while (each != to)
        {
            if (player()->board()->getPiece(each) != nullptr)
            {
                return false;
            }
            each.x = Horizontal(int(each.x) + incX);
            each.y = Vertical(int(each.y) + incY);
        }
        return true;
    };

    int diffX = int(to.x) - int(coord().x);
    int diffY = int(to.y) - int(coord().y);

    int incX = (diffX > 0) ? 1 : -1;
    int incY = (diffY > 0) ? 1 : -1;

    Coordinates coor{ Horizontal(int(coord().x) + incX), Vertical(int(coord().y) + incY) };
    
    return isValidRoute(diffX, diffY) && isClearRoute(incX, incY, coor);
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
