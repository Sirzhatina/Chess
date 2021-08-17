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
    std::array<std::array<Traits::Square*, Traits::boardSize>, Traits::boardSize> board;

    Player* players[2]{ nullptr, nullptr };
public:
    Board();
    ~Board();

    void addPlayer(Player* pl);

    void setPiece(Piece* p, Traits::Coordinates coord);

    inline const Piece* getPiece(Traits::Coordinates coord);
    inline Traits::Square* getSquare(Traits::Coordinates coord);
};

Traits::Square* Board::getSquare(Traits::Coordinates coord) { return board[Traits::boardSize - int(coord.y) - 1][int(coord.x)]; }
const Piece* Board::getPiece(Traits::Coordinates coord) { return board[Traits::boardSize - int(coord.y) - 1][int(coord.x)]->piece; }

#endif //CHESS_BOARD_H
