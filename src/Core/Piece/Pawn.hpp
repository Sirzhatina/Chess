#pragma once

#include "Piece.hpp"

namespace Chess
{
class Pawn: public Piece
{
    bool isValidAttack(Coordinates to) const;
protected:
    bool isValidRoute(Coordinates to) const override;
    bool isClearRoute(Coordinates to) const override;

public:
    Pawn(const Player* p, Coordinates coord): Piece(p, coord) { }

    bool isAbleToMove() const override;
};
}