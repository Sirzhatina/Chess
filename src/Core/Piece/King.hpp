#pragma once

#include "Piece.hpp"

namespace Chess
{
class King: public Piece
{
public:
    King(const Player* p, Coordinates coord): Piece(p, coord) { }

    bool isPossibleMove(Coordinates to) const override;
    bool isAbleToMove() const override;
    std::vector<Coordinates> squaresBefore(Coordinates to) const override;
};
}
