#pragma once

#include "Piece.hpp"

namespace Chess
{
class Pawn: public Piece
{
public:
    Pawn(const Player* p, Coordinates coord): Piece(p, coord) { }

    bool isPossibleMove(Coordinates to) const override;
    bool isAbleToMove() const;
    std::vector<Coordinates> squaresBefore(Coordinates to) const override;
};
}