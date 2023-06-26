#pragma once

#include "Piece.hpp"

namespace Chess
{
class Queen: public Piece
{
protected:
    bool isValidRoute(Coordinates to) const override;
    bool isClearRoute(Coordinates to) const override;
public:
    Queen(const Player* p, Coordinates coord): Piece(p, coord) { }

    bool isAbleToMove() const override;
};
}
