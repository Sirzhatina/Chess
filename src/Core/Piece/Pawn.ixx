export module Pawn;

import Piece;

export namespace Core
{
class Pawn: public Piece
{
public:
    Pawn(const Player* p, Coordinates coord): Piece(p, coord) { }

    bool isPossibleMove(Coordinates to) const override;
    bool isAbleToMove() const override;
    std::vector<Coordinates> squaresBefore(Coordinates to) const override;
};
}