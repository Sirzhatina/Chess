#include "Rook.hpp"
#include "../Player.hpp"

namespace Chess
{
bool Rook::isPossibleMove(Coordinates to) const 
{ 
    auto isValidRoute = [this, to](bool horizontal, bool vertical) 
    { 
        return !isSameSquare(to) && !isFriendlySquare(to) && !(horizontal && vertical);
    };
    auto isClearRoute = [this, to](bool horizontal)
    {
        auto clearSquare = [this](Coordinates c) { return player()->board()->getPiece(c) == nullptr; };

        Coordinates coor;
        int increment = 0;
        if (horizontal)
        {
            increment = (int(to.x) - int(coord().x) > 0) ? 1 : -1;
            coor = { Horizontal(int(coord().x) + increment), coord().y };
            
            while (coor != to)
            {
                if (!clearSquare(coor))
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
                if (!clearSquare(coor))
                {
                    return false;
                }
                coor.y = Vertical(int(coor.y) + increment);
            }
        }
        return true;
    };

    bool horizontal = to.x != coord().x;
    bool vertical   = to.y != coord().y;

    return isValidRoute(horizontal, vertical) && isClearRoute(horizontal);
}

bool Rook::isAbleToMove() const
{
    /*
                (0, 1)
        (-1, 0)   R   (1, 0)
               (0, -1)
    */
    auto source = coord();
    return source.tryShift(0, 1)  && isPossibleMove(source) ||
           source.tryShift(0, -1) && isPossibleMove(source) ||
           source.tryShift(1, 0)  && isPossibleMove(source) ||
           source.tryShift(-1, 0) && isPossibleMove(source);
}

std::vector<Coordinates> Rook::squaresBefore(Coordinates to) const
{
    std::vector<Coordinates> result{ coord() };

    bool horizontally = coord().x != to.x;
    bool vertically   = coord().y != to.y;

    if (!(coord().x != to.x && coord().y != to.y))
    {
        auto coor = coord();
        if (coord().x != to.x)
        {
            int incX = int(to.x) - int(coord().x) > 0 ? 1 : -1;

            coor.x = Horizontal(int(coor.x) + incX);
            while (coor != to)
            {
                result.push_back(coor);
                coor.x = Horizontal(int(coor.x) + incX);
            }
        }
        else
        {
            int incY = int(to.y) - int(coord().y) > 0 ? 1 : -1;

            coor.y = Vertical(int(coor.y) + incY);
            while (coor != to)
            {
                result.push_back(coor);
                coor.y = Vertical(int(coor.y) + incY);
            }
        }
    }
    return result;
}
}