//
// Created by Sirzh on 15.04.2021.
//

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include "..\Primitives.h"
#include <string>
#include <vector>

namespace Chess
{
class Board;
class Player;

class Piece {
    const Player* player;
    Board*        board;
    const Color   color;
    Coordinates   currentCoord;
    bool          firstMove{ true };

public:
    Piece(const Player* p, Coordinates coord);
    virtual ~Piece() = default;

    inline virtual bool possibleMove(Coordinates to) const = 0;
    virtual std::vector<Coordinates> squaresBefore(Coordinates to) const = 0;
    
    void setCoordinates(Coordinates to);

    const Player* getPlayer()   const { return player; }
    Board*        getBoard()    const { return board; }
    Color         getColor()    const { return color; }
    Coordinates   getCoord()    const { return currentCoord; }
    bool          isFirstMove() const { return firstMove; }
};
bool Piece::possibleMove(Coordinates to) const { return getCoord() != NULLPOS; }

class Pawn: public Piece {
    bool possibleAttack(Coordinates to) const;

public:
    Pawn(const Player* p, Coordinates coord): Piece(p, coord) { }

    inline bool possibleMove(Coordinates to) const override;
    static bool correctRoute(const Pawn& p, Coordinates to);

    std::vector<Coordinates> squaresBefore(Coordinates to) const override
    {
        return std::vector<Coordinates>{ getCoord() };
    }
};
bool Pawn::possibleMove(Coordinates to) const { return (possibleAttack(to) || correctRoute(*this, to)) && Piece::possibleMove(to); }


class Knight: public Piece {
public:
    Knight(const Player* p, Coordinates coord): Piece(p, coord) { }

    inline bool possibleMove(Coordinates to) const override;
    static bool correctRoute(Coordinates from, Coordinates to, const Board* b = nullptr);


    std::vector<Coordinates> squaresBefore(Coordinates to) const override
    {
        return std::vector<Coordinates>{ getCoord() };
    }
};
bool Knight::possibleMove(Coordinates to) const { return correctRoute(getCoord(), to) && Piece::possibleMove(to); }

class Bishop: public Piece {
public:
    Bishop(const Player* p, Coordinates coord): Piece(p, coord) { }

    inline bool possibleMove(Coordinates to) const override;
    static bool correctRoute(Coordinates from, Coordinates to, const Board* b);

    std::vector<Coordinates> squaresBefore(Coordinates to) const override;
};
bool Bishop::possibleMove(Coordinates to) const { return correctRoute(getCoord(), to, getBoard()) && Piece::possibleMove(to); }

class Rook: public Piece {
public:
    Rook(const Player* p, Coordinates coord): Piece(p, coord) { }

    inline bool possibleMove(Coordinates to) const override;
    static bool correctRoute(Coordinates from, Coordinates to, const Board* b);

    std::vector<Coordinates> squaresBefore(Coordinates to) const override;
};
bool Rook::possibleMove(Coordinates to) const { return correctRoute(getCoord(), to, getBoard()) && Piece::possibleMove(to); }

class Queen: public Piece {
public:
    Queen(const Player* p, Coordinates coord): Piece(p, coord) { }

    inline bool possibleMove(Coordinates to) const override;
    static bool correctRoute(Coordinates from, Coordinates to, const Board* b);

    std::vector<Coordinates> squaresBefore(Coordinates to) const override;
};
bool Queen::possibleMove(Coordinates to) const { return correctRoute(getCoord(), to, getBoard()) && Piece::possibleMove(to); }

class King: public Piece {
public:
    King(const Player* p, Coordinates coord): Piece(p, coord) { }

    bool possibleMove(Coordinates to) const override { return correctRoute(*this, getCoord(), to); }
    static bool correctRoute(const King& k, Coordinates from, Coordinates to);

    std::vector<Coordinates> squaresBefore(Coordinates to) const override { return std::vector<Coordinates>{ getCoord() }; }
};
} // ends namespace Chess
#endif //CHESS_PIECE_H