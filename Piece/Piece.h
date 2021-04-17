//
// Created by Sirzh on 15.04.2021.
//

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

enum class Horizontal { A = 1, B, C, D, E, F, G, H };
enum class Vertical { one = 1, two, three, four, five, six, seven, eight };

struct Coordinates {
    Horizontal x;
    Vertical y;
};


class Piece {
    Coordinates coord;
public:
    explicit Piece(Coordinates c);

    virtual ~Piece() = 0;

    virtual void Move();

    virtual Coordinates getCoord() const;
};

class Pawn: public Piece {

    bool firstMove = true;
public:
    Pawn(Coordinates c);

    void Move() final;
};


class Knight: public Piece {
public:
    explicit Knight(Coordinates c);
};

class Bishop: public Piece {
public:
    explicit Bishop(Coordinates c);
};

class Rook: public Piece {
public:
    explicit Rook(Coordinates c);
};

class Queen: public Piece {
public:
    explicit Queen(Coordinates c);
};

class King: public Piece {
public:
    explicit King(Coordinates c);
};




#endif //CHESS_PIECE_H
