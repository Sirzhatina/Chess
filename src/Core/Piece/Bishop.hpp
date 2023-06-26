#pragma once

#include "Piece.hpp"

namespace Chess
{
class Bishop: public Piece
{
protected:
    bool isValidRoute(Coordinates to) const override;
    bool isClearRoute(Coordinates to) const override;

    friend class Queen;

public:
    Bishop(const Player* p, Coordinates coord): Piece(p, coord) { }

    bool isAbleToMove() const override;
};
}
