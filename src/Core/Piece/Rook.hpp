#pragma once

#include "Piece.hpp"

namespace Chess
{
class Rook: public Piece
{
protected:
    bool isValidRoute(Coordinates to) const override;
    bool isClearRoute(Coordinates to) const override;
    
    friend class Queen;

public:
    Rook(const Player* p, Coordinates coord): Piece(p, coord) { }

    bool isAbleToMove() const override;
    std::vector<Coordinates> squaresBefore(Coordinates to) const override;
};
}