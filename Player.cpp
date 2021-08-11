//
// Created by Sirzh on 15.04.2021.
//

#include "Player.h"
#include "Piece\Piece.h"
#include "Board.h"
#include "Square.h"


Player::Player(Board* b, Traits::Color c)
: board(b)
, color(c)
{
    board->addPlayer(this);

    Traits::Vertical startOfPawns = color == Traits::Color::WHITE ? Traits::Vertical::two : Traits::Vertical::seven;
    Traits::Vertical startOfOthers = color == Traits::Color::WHITE ? Traits::Vertical::one : Traits::Vertical::eight;

    unsigned alongLine = 0;
    for (auto& pwn: pawn)
    {
        pwn = new Pawn{this, color, &board->getSquare(Traits::Coordinates{ Traits::Horizontal(alongLine++), startOfPawns }) };
    }

    alongLine = 0;
    for (unsigned i = 0, inc = 1; i < PAIR_PIECES; i++, alongLine += 6, inc *= -1)
    {
        rook[i] = new Rook{ this, color, &board->getSquare(Traits::Coordinates{ Traits::Horizontal(alongLine += inc), startOfOthers }) };
        knight[i] = new Knight{ this, color, &board->getSquare(Traits::Coordinates{ Traits::Horizontal(alongLine += inc), startOfOthers }) };
        bishop[i] = new Bishop{ this, color, &board->getSquare(Traits::Coordinates{ Traits::Horizontal(alongLine += inc), startOfOthers }) };
    }

    // Queen prefers corresponding color
    queen = new Queen{ this, color, &board->getSquare(Traits::Coordinates{ Traits::Horizontal::D, startOfOthers }) };
    king = new King{ this, color, &board->getSquare(Traits::Coordinates{ Traits::Horizontal::E, startOfOthers }) };
}

bool Player::move(Traits::Coordinates from, Traits::Coordinates to)
{

}