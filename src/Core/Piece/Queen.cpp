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
}
