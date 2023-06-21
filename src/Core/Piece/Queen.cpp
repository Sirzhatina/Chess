#include "Queen.hpp"
#include "Bishop.hpp"
#include "Rook.hpp"

namespace Chess
{
bool Queen::isValidRoute(Coordinates to) const
{
    return Bishop{player(), coord()}.isValidRoute(to) || Rook{player(), coord()}.isValidRoute(to);
}

bool Queen::isClearRoute(Coordinates to) const
{
    return Bishop{player(), coord()}.isClearRoute(to) || Rook{player(), coord()}.isClearRoute(to);
}

bool Queen::isAbleToMove() const
{
    return Bishop{player(), coord()}.isAbleToMove() || Rook{player(), coord()}.isAbleToMove();
}

std::vector<Coordinates> Queen::squaresBefore(Coordinates to) const
{
    auto rook   = Rook{ player(), coord() }.squaresBefore(to);
    auto bishop = Bishop{ player(), coord() }.squaresBefore(to);

    std::vector<Coordinates> result{ coord() };
    result.reserve(rook.size() + bishop.size() + 1);

    for (auto coor : rook)
    {
        result.push_back(coor);
    }
    for (auto coor : bishop)
    {
        result.push_back(coor);
    }
    return result;
}
}
