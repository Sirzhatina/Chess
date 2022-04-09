#pragma once

#include "Piece.hpp"

namespace Chess
{
class Bishop: public Piece
{
public:
    Bishop(const Player* p, Coordinates coord): Piece(p, coord) { }

    bool isPossibleMove(Coordinates to) const override;
    
    std::vector<Coordinates> squaresBefore(Coordinates to) const override;
};
}
