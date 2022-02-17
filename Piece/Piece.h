//
// Created by Sirzh on 15.04.2021.
//

#pragma once

#include "..\Primitives.h"
#include <string>
#include <vector>

namespace Chess
{
class Board;
class Player;

class Piece
{
    const Player* _player;
    Coordinates   _currentCoord;
    bool          _firstMove{ true };

public:
    Piece(const Player* p, Coordinates coord);
    virtual ~Piece() = default;

    virtual bool                     possibleMove(Coordinates to)  const = 0;
    virtual std::vector<Coordinates> squaresBefore(Coordinates to) const = 0;
    
    void setCoordinates(Coordinates to);

    const Player* player()      const { return _player; }
    Coordinates   coord()       const { return _currentCoord; }
    bool          isFirstMove() const { return _firstMove; }
    bool          isOnBoard()   const { _currentCoord != NULLPOS; }
};


class Pawn: public Piece
{
    bool possibleAttack(Coordinates to) const;

public:
    Pawn(const Player* p, Coordinates coord): Piece(p, coord) { }

    bool possibleMove(Coordinates to) const override;
    static bool correctRoute(const Pawn& p, Coordinates to);
    std::vector<Coordinates> squaresBefore(Coordinates to) const override;
};


class Knight: public Piece
{
public:
    Knight(const Player* p, Coordinates coord): Piece(p, coord) { }

    bool possibleMove(Coordinates to) const override;
    static bool correctRoute(Coordinates from, Coordinates to, const Board* b = nullptr);
    std::vector<Coordinates> squaresBefore(Coordinates to) const override;
};


class Bishop: public Piece
{
public:
    Bishop(const Player* p, Coordinates coord): Piece(p, coord) { }

    bool possibleMove(Coordinates to) const override;
    static bool correctRoute(Coordinates from, Coordinates to, const Board* b);

    std::vector<Coordinates> squaresBefore(Coordinates to) const override;
};


class Rook: public Piece
{
public:
    Rook(const Player* p, Coordinates coord): Piece(p, coord) { }

    bool possibleMove(Coordinates to) const override;
    static bool correctRoute(Coordinates from, Coordinates to, const Board* b);

    std::vector<Coordinates> squaresBefore(Coordinates to) const override;
};


class Queen: public Piece
{
public:
    Queen(const Player* p, Coordinates coord): Piece(p, coord) { }

    bool possibleMove(Coordinates to) const override;
    static bool correctRoute(Coordinates from, Coordinates to, const Board* b);

    std::vector<Coordinates> squaresBefore(Coordinates to) const override;
};


class King: public Piece
{
public:
    King(const Player* p, Coordinates coord): Piece(p, coord) { }

    bool possibleMove(Coordinates to) const override;
    static bool correctRoute(const King& k, Coordinates from, Coordinates to);
    std::vector<Coordinates> squaresBefore(Coordinates to) const override;
};
} // ends namespace Chess