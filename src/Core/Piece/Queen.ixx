export module Queen;

import Piece;

export namespace Core
{
class Queen: public Piece
{
public:
    Queen(const Player* p, Coordinates coord): Piece(p, coord) { }

    bool isPossibleMove(Coordinates to) const override;
    bool isAbleToMove() const override;
    std::vector<Coordinates> squaresBefore(Coordinates to) const override;
};
}
