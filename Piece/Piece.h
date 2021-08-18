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
    using Coordinates = Traits::Coordinates;
    static std::string errMsg;
    void setCoordinates(Coordinates coord) { currentCoord = coord; }

private:
    const Player* player;
    Board* board;
    const Traits::Color color;
    Coordinates currentCoord;

public:
    Piece(const Player* p, Coordinates coord);

    virtual ~Piece() = default;

    virtual bool possibleMove(Traits::Coordinates to) const = 0;

    const Player* getPlayer() const { return player; }
    Board* getBoard() const { return board; }
    Traits::Color getColor() const { return color; }
    Traits::Coordinates getCoord() const { return currentCoord; }
};

class Pawn: public Piece {
    bool firstMove{ true };

    bool whiteAttack(Coordinates from, Coordinates to) const { return int(to.y) - int(from.y) == 1 && std::abs(int(to.x) - int(from.x)) == 1; }
    bool blackAttack(Coordinates from, Coordinates to) const { return int(from.y) - int(to.y) == 1 && std::abs(int(to.x) - int(from.x)) == 1; }
public:
    Pawn(Player* p, Traits::Coordinates coord): Piece(p, coord) { }

    bool possibleMove(Traits::Coordinates to) const override;
};


class Knight: public Piece {
public:
    Knight(Player* p, Traits::Coordinates coord);

    bool possibleMove(Traits::Coordinates to) const override;
};

class Bishop: public Piece {
public:
    Bishop(Player* p, Traits::Coordinates coord);

    bool possibleMove(Traits::Coordinates to) const override;
};

class Rook: public Piece {
public:
    Rook(Player* p, Traits::Coordinates coord);

    bool possibleMove(Traits::Coordinates to) const override;
};

class Queen: public Piece {
public:
    Queen(Player* p, Traits::Coordinates coord);

    bool possibleMove(Traits::Coordinates to) const override;
};

class King: public Piece {
public:
    King(Player* p, Traits::Coordinates coord);

    bool possibleMove(Traits::Coordinates to) const override;
};

#endif //CHESS_PIECE_H
