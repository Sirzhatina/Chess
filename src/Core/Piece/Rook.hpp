#pragma once

#include "Piece.hpp"

namespace Chess
{
class Rook: public Piece
{

public:
    Rook(const Player* p, Coordinates coord): Piece(p, coord) { }

    bool isPossibleMove(Coordinates to) const override;
    bool isAbleToMove() const override;
    std::vector<Coordinates> squaresBefore(Coordinates to) const override;
};
}