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

bool Piece::isFriendlySquare(Coordinates square) const
{
    auto piece = _player->board()->getPiece(square); 
    return piece ? _player == piece->_player : false; 
}

bool Piece::isPossibleMove(Coordinates to) const
{ 
    return isValidRoute(to) && isClearRoute(to); 
}

std::vector<Coordinates> Piece::squaresBefore(Coordinates to) const { return { coord() }; }

void Piece::setCoordinates(Coordinates to)
{
    _firstMove = false;
    _currentCoord = to;
}
} // namespace Chess
