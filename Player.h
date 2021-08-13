//
// Created by Sirzh on 15.04.2021.
//

#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H

#include "Traits.h"

class Board;
class Piece;

class Player {

    static constexpr auto PAWNS = 8;
    static constexpr auto PAIR_PIECES = 2;

    const Traits::Color color;

    bool check{ false };
    bool checkmate{ false };

    Board* board;

    Piece* pawn[PAWNS];

    Piece* knight[PAIR_PIECES];
    Piece* bishop[PAIR_PIECES];
    Piece* rook[PAIR_PIECES];

    Piece* queen;
    Piece* king;

public:
    Player(Board* b, Traits::Color c);

    void move(Traits::Coordinates from, Traits::Coordinates to);

    Traits::Color getColor() const { return color; }

    bool isCheck() const { return check; }
    bool isCheckmate() const { return checkmate; }


    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
};

#endif //CHESS_PLAYER_H
