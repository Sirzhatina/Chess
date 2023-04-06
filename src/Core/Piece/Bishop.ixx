export module Bishop;

import Piece;

export namespace Core
{
class Bishop: public Piece
{
public:
    Bishop(const Player* p, Coordinates coord): Piece(p, coord) { }

    bool isPossibleMove(Coordinates to) const override;
    bool isAbleToMove() const override;
    std::vector<Coordinates> squaresBefore(Coordinates to) const override;
};
}
