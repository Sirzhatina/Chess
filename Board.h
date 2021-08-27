//
// Created by Sirzh on 10.05.2021.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <array>
#include "Traits.h"

class Player;
class Piece;

class Board {
public:
    struct Square { const Traits::Coordinates coord; Piece* piece{ nullptr }; };

    Board();
    ~Board();

    void addPlayer(Player* pl);

    Piece* setPiece(Piece* p, Traits::Coordinates coord);
    inline const Piece* getPiece(Traits::Coordinates coord) const;

private:
    std::array<std::array<Square, Traits::boardSize>, Traits::boardSize>* board{};
    Player* players[2]{ nullptr, nullptr };

    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
};

const Piece* Board::getPiece(Traits::Coordinates coord) const { return (*board)[Traits::boardSize - int(coord.y) - 1][int(coord.x)].piece; }

#endif //CHESS_BOARD_H
