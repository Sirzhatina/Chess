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
    Square* currentSqr;
public:
    Piece(const Player* p, Traits::Color c, Square* sqr);

    virtual ~Piece() = default;

    virtual void move(Traits::Coordinates to) = 0;

    const Player* getPlayer() const { return player; }
    const Square* getCoord() const { return currentSqr; }
};

class Pawn: public Piece {
    bool firstMove{ true };
public:
    Pawn(Player* p, Traits::Color c, Square* sqr): Piece(p, c, sqr) { }

    void move(Traits::Coordinates to) override;
};


class Knight: public Piece {
public:
    Knight(Player* p, Traits::Color c, Square* sqr);

    void move(Traits::Coordinates to) override;
};

class Bishop: public Piece {
public:
    Bishop(Player* p, Traits::Color c, Square* sqr);

    void move(Traits::Coordinates to) override;
};

class Rook: public Piece {
public:
    Rook(Player* p, Traits::Color c, Square* sqr);

    void move(Traits::Coordinates to) override;
};

class Queen: public Piece {
public:
    Queen(Player* p, Traits::Color c, Square* sqr);

    void move(Traits::Coordinates to) override;
};

class King: public Piece {
public:
    King(Player* p, Traits::Color c, Square* sqr);

    void move(Traits::Coordinates to) override;
};


#endif //CHESS_PIECE_H
