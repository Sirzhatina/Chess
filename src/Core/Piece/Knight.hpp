#pragma once

#include "Piece.hpp"

namespace Chess
{
class Knight: public Piece
{
protected:
    bool isValidRoute(Coordinates to) const override;
    bool isClearRoute(Coordinates to) const override;

public:
    Knight(const Player* p, Coordinates coord): Piece(p, coord) { }

    bool isAbleToMove() const override;
};
}
