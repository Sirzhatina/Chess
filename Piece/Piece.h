//
// Created by Sirzh on 15.04.2021.
//

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include "..\Traits.h"
#include <string>

class Square;
class Player;


class Piece {
protected:
    static std::string errMsg;

private:
    const Player*       player;
    Board*              board;
    const Traits::Color color;
    Traits::Coordinates currentCoord;
    bool                firstMove{ true };

public:
    Piece(const Player* p, Traits::Coordinates coord);
    virtual ~Piece() = default;

    virtual bool possibleMove(Traits::Coordinates to) const = 0;
    
    void setCoordinates(Traits::Coordinates to);

    const Player*       getPlayer()   const { return player; }
    Board*              getBoard()    const { return board; }
    Traits::Color       getColor()    const { return color; }
    Traits::Coordinates getCoord()    const { return currentCoord; }
    bool                isFirstMove() const { return firstMove; }
};

class Pawn: public Piece {
    bool possibleAttack(Traits::Coordinates to) const;

public:
    Pawn(const Player* p, Traits::Coordinates coord): Piece(p, coord) { }

    bool possibleMove(Traits::Coordinates to) const override { return possibleAttack(to) || correctRoute(*this, to); }
    static bool correctRoute(const Pawn& p, Traits::Coordinates to);
};


class Knight: public Piece {
public:
    Knight(const Player* p, Traits::Coordinates coord);

    bool possibleMove(Traits::Coordinates to) const override { return correctRoute(getCoord(), to); }
    static bool correctRoute(Traits::Coordinates from, Traits::Coordinates to, const Board* b = nullptr);
};

class Bishop: public Piece {
public:
    Bishop(const Player* p, Traits::Coordinates coord);

    bool possibleMove(Traits::Coordinates to) const override { return correctRoute(getCoord(), to, getBoard()); }
    static bool correctRoute(Traits::Coordinates from, Traits::Coordinates to, const Board* b);
};

class Rook: public Piece {
public:
    Rook(const Player* p, Traits::Coordinates coord);

    bool possibleMove(Traits::Coordinates to) const override { return correctRoute(getCoord(), to, getBoard()); }
    static bool correctRoute(Traits::Coordinates from, Traits::Coordinates to, const Board* b);
};

class Queen: public Piece {
public:
    Queen(const Player* p, Traits::Coordinates coord);

    bool possibleMove(Traits::Coordinates to) const override { return correctRoute(getCoord(), to, getBoard()); }
    static bool correctRoute(Traits::Coordinates from, Traits::Coordinates to, const Board* b);
};

class King: public Piece {
public:
    King(const Player* p, Traits::Coordinates coord);

    bool possibleMove(Traits::Coordinates to) const override { return correctRoute(*this, getCoord(), to); }
    static bool correctRoute(const King& k, Traits::Coordinates from, Traits::Coordinates to);

 //   bool possibleCastling(Traits::Coordinates to) const;
};

#endif //CHESS_PIECE_H