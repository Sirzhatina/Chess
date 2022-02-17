//
// Created by Sirzh on 10.05.2021.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <array>
#include "Primitives.h"

namespace Chess 
{
class Player;
class Piece;

// Mayer's singleton
class Board {
public:
    struct Square { Coordinates coord; Piece* piece{ nullptr }; };

    // only one instance
    static Board& getInstance()
    {
        static Board b;
        return b;
    }

    ~Board() = default;

    void addPlayer(Player* pl);

    Piece* setPiece(Piece* p, Coordinates coord);
    inline const Piece* getPiece(Coordinates coord) const;

private:
    std::array<std::array<Square, boardSize>, boardSize> board;
    Player* players[2]{ nullptr, nullptr };

    // forbidden instantiation
    Board();

    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
};
const Piece* Board::getPiece(Coordinates coord) const { return board[boardSize - int(coord.y) - 1][int(coord.x)].piece; }
} // ends namespace Chess

#endif //CHESS_BOARD_H
