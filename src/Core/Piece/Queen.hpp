#pragma once

#include "Piece.hpp"

namespace Chess
{
class Queen: public Piece
{
public:
    Queen(const Player* p, Coordinates coord): Piece(p, coord) { }

    bool isPossibleMove(Coordinates to) const override;
    bool isAbleToMove() const override;
    std::vector<Coordinates> squaresBefore(Coordinates to) const override;
};
}
