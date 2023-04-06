export module Knight;

import Piece;

export namespace Core
{
class Knight: public Piece
{
public:
    Knight(const Player* p, Coordinates coord): Piece(p, coord) { }

    bool isPossibleMove(Coordinates to) const override;
    bool isAbleToMove() const override;
    std::vector<Coordinates> squaresBefore(Coordinates to) const override;
};
}
