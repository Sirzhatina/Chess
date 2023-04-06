export module Board;

import std.core;
import Primitives;

export namespace Core 
{
class Player;
class Piece;

class Board 
{
public:
    struct Square 
    { 
        Coordinates coord; 
        const Piece* piece{ nullptr }; 
    };

    Board();
    ~Board() = default;

    void addPlayer(Player* pl);

    const Player* enemyOf(const Player* p) const;

    const Piece* setPiece(const Piece* p, Coordinates coord);
    const Piece* getPiece(Coordinates coord) const;

private:
    std::array<std::array<Square, boardSize>, boardSize> board;

    const Player* _white{ nullptr };
    const Player* _black{ nullptr };

    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
};
} // ends namespace Chess
