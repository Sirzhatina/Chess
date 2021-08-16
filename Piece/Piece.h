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
    const Traits::Color color;
    Coordinates currentCoord;

public:
    Piece(const Player* p, Coordinates coord);

    virtual ~Piece() = default;

    virtual bool possibleMove(Traits::Coordinates to) = 0;

    const Player* getPlayer() const { return player; }
    Traits::Color getColor() const { return color; }
    Traits::Coordinates getCoord() const { return currentCoord; }
};

class Pawn: public Piece {
    bool firstMove{ true };

    bool whiteAttack(Coordinates from, Coordinates to) const { return int(to.v) - int(from.v) == abs(int(to.h) - int(from.h)); }
    bool blackAttack(Coordinates from, Coordinates to) const { return int(from.v) - int(to.v) == abs(int(to.h) - int(from.h)); }
public:
    Pawn(Player* p, Traits::Coordinates coord): Piece(p, coord) { }

    bool possibleMove(Traits::Coordinates to) override;
};


class Knight: public Piece {
public:
    Knight(Player* p, Traits::Coordinates coord);

    bool possibleMove(Traits::Coordinates to) override;
};

class Bishop: public Piece {
public:
    Bishop(Player* p, Traits::Coordinates coord);

    bool possibleMove(Traits::Coordinates to) override;
};

class Rook: public Piece {
public:
    Rook(Player* p, Traits::Coordinates coord);

    bool possibleMove(Traits::Coordinates to) override;
};

class Queen: public Piece {
public:
    Queen(Player* p, Traits::Coordinates coord);

    bool possibleMove(Traits::Coordinates to) override;
};

class King: public Piece {
public:
    King(Player* p, Traits::Coordinates coord);

    bool possibleMove(Traits::Coordinates to) override;
};

#endif //CHESS_PIECE_H
