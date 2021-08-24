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

    bool possibleCastling(Traits::Coordinates to) const;
    void castling(Traits::Coordinates to);

    bool isOwner(const Piece* piece) const { return piece->getPlayer() == this; }
    bool friendlySquare(Traits::Coordinates to) const { return board->getPiece(to) ? board->getPiece(to)->getPlayer() == this : false; }

public:
    Player(Board* b, Traits::Color c);

    void move(Traits::Coordinates from, Traits::Coordinates to);

    Traits::Color getColor() const { return color; }

    Board* getBoard() const { return board; }
    Traits::Coordinates getKingCoord() const { king->getCoord(); }

    bool accessToSquare(Traits::Coordinates to) const;
    void setCheck(bool ch) { check = ch; }

    bool isCheck() const { return check; }
    bool isCheckmate() const { return checkmate; }


    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
};

#endif //CHESS_PLAYER_H
