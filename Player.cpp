//
// Created by Sirzh on 15.04.2021.
//

#include "Player.h"
#include "Piece\Piece.h"
#include "Board.h"
#include <typeinfo>


Player::Player(Board* b, Traits::Color c)
: board(b)
, color(c)
{
    board->addPlayer(this);

    Traits::Vertical startOfPawns = (color == Traits::Color::WHITE) ? Traits::Vertical::two : Traits::Vertical::seven;
    Traits::Vertical startOfOthers = (color == Traits::Color::WHITE) ? Traits::Vertical::one : Traits::Vertical::eight;

    unsigned alongLine = 0;
    for (auto& pwn: pawn)
    {
        pwn = new Pawn{ this, Traits::Coordinates{ Traits::Horizontal{ alongLine }, startOfPawns } };
        board->setPiece(pwn, pwn->getCoord());
    }

    alongLine = -1;
    for (unsigned i = 0, inc = 1; i < PAIR_PIECES; i++)
    {
        rook[i] = new Rook{ this, Traits::Coordinates{ Traits::Horizontal{ alongLine += inc }, startOfOthers } };
        board->setPiece(rook[i], rook[i]->getCoord());

        knight[i] = new Knight{ this, Traits::Coordinates{ Traits::Horizontal{ alongLine += inc }, startOfOthers } };
        board->setPiece(knight[i], knight[i]->getCoord());

        bishop[i] = new Bishop{ this, Traits::Coordinates{ Traits::Horizontal{ alongLine += inc }, startOfOthers } };
        board->setPiece(bishop[i], bishop[i]->getCoord());

        inc *= -1;
        alongLine += 6;
    }

    // Queen prefers corresponding color
    queen = new Queen{ this, Traits::Coordinates{ Traits::Horizontal::D, startOfOthers } };
    board->setPiece(queen, queen->getCoord());

    king = new King{ this, Traits::Coordinates{ Traits::Horizontal::E, startOfOthers } };
    board->setPiece(king, king->getCoord());
}

bool Player::possibleCastling(Traits::Coordinates to) const
{
    if (king->isFirstMove())
    {
        int diffX = int(to.y) - int(king->getCoord().y);

        // 2 means king moves on 2 squares left and -2 - two squares right
        return diffX ==  2 &&  !board->getPiece({ Traits::Horizontal::G, king->getCoord().y }) && rook[1]->isFirstMove() ||
               diffX == -2 &&  !board->getPiece({ Traits::Horizontal::C, king->getCoord().y }) && rook[0]->isFirstMove();
    }
    return false;
}

bool Player::accessToSquare(Traits::Coordinates to) const
{
    for (const auto p : pawn)
    {
        if (p->possibleMove(to))
        {
            return true;
        }
    }
    if (rook[0]->possibleMove(to)   || rook[1]->possibleMove(to)   ||
        knight[0]->possibleMove(to) || knight[1]->possibleMove(to) ||
        bishop[0]->possibleMove(to) || bishop[1]->possibleMove(to) ||
        queen->possibleMove(to))
    {
        return true;   
    }
    return false;
}

void Player::move(Traits::Coordinates from, Traits::Coordinates to)
{
    auto piece = const_cast<Piece*>(board->getPiece(from));
    if (this == piece->getPlayer())
    {
        if (board->getPiece(to)->getPlayer() != this && piece->possibleMove(to))
        {
            if (piece == king && king->isFirstMove())
            {
                if (to.x == Traits::Horizontal::G && rook[1]->isFirstMove())
                {
                    Traits::Coordinates coor{ Traits::Horizontal::F, rook[1]->getCoord().y };
                    rook[1]->setCoordinates(coor);
                    board->setPiece(rook[1], coor);
                }
                else if (to.x == Traits::Horizontal::C && rook[0]->isFirstMove())
                {
                    Traits::Coordinates coor{ Traits::Horizontal::D, rook[0]->getCoord().y };
                    rook[1]->setCoordinates(coor);
                    board->setPiece(rook[0], coor);
                }
            }
            piece->setCoordinates(to);
            board->setPiece(piece, to);
        } 
    }
}