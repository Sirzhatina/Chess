//
// Created by Sirzh on 15.04.2021.
//

#include <stdexcept>
#include <cstdlib>
#include "Piece.h"
#include "..\Player.h"
#include "..\Board.h"

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

std::vector<Coordinates> Piece::squaresBefore(Coordinates to) const { return { coord() }; }

void Piece::setCoordinates(Coordinates to)
{
    _firstMove = false;
    _currentCoord = to;
}
} // namespace Chess
