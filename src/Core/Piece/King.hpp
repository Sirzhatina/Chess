#pragma once

#include "Piece.hpp"

namespace Chess
{
class King: public Piece
{
protected:
    bool isValidRoute(Coordinates to) const override;
    bool isClearRoute(Coordinates to) const override;

public:
    King(const Player* p, Coordinates coord): Piece(p, coord) { }

    bool isAbleToMove() const override;
};
}
