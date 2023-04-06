module Piece;

import std.core;
import Board;
import Player;

namespace Core
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
