//
// Created by Sirzh on 15.04.2021.
//

#include <stdexcept>
#include <cstdlib>
#include "Piece.hpp"
#include "..\Player.hpp"
#include "..\Board.hpp"

namespace Chess
{
Piece::Piece(const Player* p, Coordinates coord)
: _player(p)
, _currentCoord(coord)
{ }

bool Piece::isAbleToMoveToSqr(Coordinates to, int x, int y) const 
{ 
    return to.tryShiftAt(x, y) && isPossibleMove(to); 
}

bool Piece::isValidRoute(Coordinates to) const
{
    return !isFriendlySquare(to) && !isSameSquare(to);
}

bool Piece::isSameSquare(Coordinates to) const
{
    return coord() == to;
}

bool Piece::isFriendlySquare(Coordinates square) const
{
    auto piece = _player->board()->getPiece(square); 
    return piece ? _player == piece->_player : false; 
}

bool Piece::isPossibleMove(Coordinates to) const
{ 
    return isValidRoute(to) && isClearRoute(to); 
}

void Piece::setCoordinates(Coordinates to)
{
    _firstMove = false;
    _currentCoord = to;
}
} // namespace Chess
