#pragma once

#include "Piece.h"

namespace Chess
{
class Knight: public Piece
{
public:
    Knight(const Player* p, Coordinates coord): Piece(p, coord) { }

    bool isPossibleMove(Coordinates to) const override;
    
    std::vector<Coordinates> squaresBefore(Coordinates to) const override;
};
}
