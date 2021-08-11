//
// Created by Sirzh on 15.04.2021.
//

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include "..\Traits.h"

class Square;
class Player;

class Piece {
    const Player* player;
    const Traits::Color color;
    Square* currentSqr;
public:
    Piece(const Player* p, Traits::Color c, Square* sqr);

    virtual ~Piece() = 0;

    virtual void Move();

    virtual Square getCoord() const;
};

class Pawn: public Piece {
    bool firstMove{ true };
public:
    Pawn(Player* p, Traits::Color c, Square* sqr): Piece(p, c, sqr) { }

    void Move() final;
};


class Knight: public Piece {
public:
    Knight(Player* p, Traits::Color c, Square* sqr);
};

class Bishop: public Piece {
public:
    Bishop(Player* p, Traits::Color c, Square* sqr);
};

class Rook: public Piece {
public:
    Rook(Player* , Traits::Color c, Square* sqr);
};

class Queen: public Piece {
public:
    Queen(Player* p, Traits::Color c, Square* sqr);
};

class King: public Piece {
public:
    King(Player* p, Traits::Color c, Square* sqr);
};




#endif //CHESS_PIECE_H
