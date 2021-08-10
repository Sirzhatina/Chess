//
// Created by Sirzh on 15.04.2021.
//

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include "..\Square.h"
#include "..\Traits.h"

class Player;

class Piece {
    Square* currentSqr;
    Player* player;
    Color col;
public:
    explicit Piece(Player* p, Square* c);

    virtual ~Piece() = 0;

    virtual void Move();

    virtual Square getCoord() const;
};

class Pawn: public Piece {
    bool firstMove{ true };
public:
    Pawn(Square c);

    void Move() final;
};


class Knight: public Piece {
public:
    explicit Knight(Square c);
};

class Bishop: public Piece {
public:
    explicit Bishop(Square c);
};

class Rook: public Piece {
public:
    explicit Rook(Square c);
};

class Queen: public Piece {
public:
    explicit Queen(Square c);
};

class King: public Piece {
public:
    explicit King(Square c);
};




#endif //CHESS_PIECE_H
