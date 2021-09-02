//
// Created by Sirzh on 10.05.2021.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <array>
#include "Traits.h"

class Player;
class Piece;

// Mayer's singleton
class Board {
public:
    struct Square { Traits::Coordinates coord; Piece* piece{ nullptr }; };

    // only one instance
    static Board& getInstance()
    {
        static Board b;
        return b;
    }

    ~Board() = default;

    void addPlayer(Player* pl);

    Piece* setPiece(Piece* p, Traits::Coordinates coord);
    inline const Piece* getPiece(Traits::Coordinates coord) const;

private:
    std::array<std::array<Square, Traits::boardSize>, Traits::boardSize> board;
    Player* players[2]{ nullptr, nullptr };

    Board();

    Board(const Board&) = delete;
    Board(Board&&) = delete;
    Board& operator=(const Board&) = delete;
    Board& operator=(Board&&) = delete;
};

const Piece* Board::getPiece(Traits::Coordinates coord) const { return board[Traits::boardSize - int(coord.y) - 1][int(coord.x)].piece; }

#endif //CHESS_BOARD_H
