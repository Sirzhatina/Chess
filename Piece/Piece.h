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
    void setCoordinates(Traits::Coordinates coord) { currentCoord = coord; }

private:
    const Player* player;
    Board* board;
    const Traits::Color color;
    Traits::Coordinates currentCoord;

public:
    Piece(const Player* p, Traits::Coordinates coord);

    virtual ~Piece() = default;

    virtual bool possibleMove(Traits::Coordinates to) const = 0;
    virtual void move(Traits::Coordinates to) = 0;

    const Player* getPlayer() const { return player; }
    Board* getBoard() const { return board; }
    Traits::Color getColor() const { return color; }
    Traits::Coordinates getCoord() const { return currentCoord; }
};

class Pawn: public Piece {
    bool firstMove{ true };

    bool possibleAttack(Traits::Coordinates to) const;
public:
    Pawn(Player* p, Traits::Coordinates coord): Piece(p, coord) { }

    bool possibleMove(Traits::Coordinates to) const override;
    void move(Traits::Coordinates to) override;
};


class Knight: public Piece {
public:
    Knight(Player* p, Traits::Coordinates coord);

    bool possibleMove(Traits::Coordinates to) const override;
    void move(Traits::Coordinates to) override;
};

class Bishop: public Piece {
public:
    Bishop(Player* p, Traits::Coordinates coord);

    bool possibleMove(Traits::Coordinates to) const override;
    void move(Traits::Coordinates to) override;
};

class Rook: public Piece {
public:
    Rook(Player* p, Traits::Coordinates coord);

    bool possibleMove(Traits::Coordinates to) const override;
    void move(Traits::Coordinates to) override;
};

class Queen: public Piece {
public:
    Queen(Player* p, Traits::Coordinates coord);

    bool possibleMove(Traits::Coordinates to) const override;
    void move(Traits::Coordinates to) override;
};

class King: public Piece {
public:
    King(Player* p, Traits::Coordinates coord);

    bool possibleMove(Traits::Coordinates to) const override;
    void move(Traits::Coordinates to) override;
};

#endif //CHESS_PIECE_H
