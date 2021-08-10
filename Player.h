//
// Created by Sirzh on 15.04.2021.
//

#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H

#include <memory>
#include "Traits.h"
#include "Piece/Piece.h"

class Player {

    static constexpr auto PAWNS = 8;
    static constexpr auto PAIR_PIECES = 2;

    Color pieceClr;

    bool check{ false };
    bool checkmate{ false };

    Piece* pawn[PAWNS];

    Piece* knight[PAIR_PIECES];
    Piece* bishop[PAIR_PIECES];
    Piece* rook[PAIR_PIECES];

    Piece* queen;
    Piece* king;

public:
    Player(Color c);

    bool move(Square from, Square to);

    Color getColor() const { return pieceClr; }

    bool isCheck() const { return check; }
    bool isCheckmate() const { return checkmate; }


    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
};

#endif //CHESS_PLAYER_H
