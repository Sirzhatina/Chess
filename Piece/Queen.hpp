#pragma once

#include "Piece.h"

namespace Chess
{
class Queen: public Piece
{
public:
    Queen(const Player* p, Coordinates coord): Piece(p, coord) { }

    bool isPossibleMove(Coordinates to) const override;

    std::vector<Coordinates> squaresBefore(Coordinates to) const override;
};
}
