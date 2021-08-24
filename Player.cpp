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

    auto startOfPawns = (color == Traits::Color::WHITE) ? Traits::Vertical::two : Traits::Vertical::seven;
    auto startOfOthers = (color == Traits::Color::WHITE) ? Traits::Vertical::one : Traits::Vertical::eight;

    unsigned alongLine = 0;
    for (auto& pwn: pawn)
    {
        pwn = new Pawn{ this, { Traits::Horizontal{ alongLine }, startOfPawns } };
        board->setPiece(pwn, pwn->getCoord());
    }

    alongLine = -1;
    for (unsigned i = 0, inc = 1; i < PAIR_PIECES; i++)
    {
        rook[i] = new Rook{ this, { Traits::Horizontal{ alongLine += inc }, startOfOthers } };
        board->setPiece(rook[i], rook[i]->getCoord());

        knight[i] = new Knight{ this, { Traits::Horizontal{ alongLine += inc }, startOfOthers } };
        board->setPiece(knight[i], knight[i]->getCoord());

        bishop[i] = new Bishop{ this, { Traits::Horizontal{ alongLine += inc }, startOfOthers } };
        board->setPiece(bishop[i], bishop[i]->getCoord());

        inc *= -1;
        alongLine += 6;
    }

    // Queen prefers corresponding color
    queen = new Queen{ this, { Traits::Horizontal::D, startOfOthers } };
    board->setPiece(queen, queen->getCoord());

    king = new King{ this, { Traits::Horizontal::E, startOfOthers } };
    board->setPiece(king, king->getCoord());
}

bool Player::possibleCastling(Traits::Coordinates to) const
{
    if (king->isFirstMove())
    {
        if (to.y == king->getCoord().y)
        {
            if (to.x == Traits::Horizontal::G)
            {
                if (getBoard()->getPiece({ Traits::Horizontal::F, to.y }) == nullptr &&
                    getBoard()->getPiece({ Traits::Horizontal::G, to.y }) == nullptr)
                {
                    return rook[1]->isFirstMove();
                }
            }
            else if (to.x == Traits::Horizontal::C)
            {
                if (getBoard()->getPiece({ Traits::Horizontal::D, to.y }) == nullptr &&
                    getBoard()->getPiece({ Traits::Horizontal::C, to.y }) == nullptr &&
                    getBoard()->getPiece({ Traits::Horizontal::B, to.y }) == nullptr)
                {
                    return rook[0]->isFirstMove();
                }
            }
        }
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
            if (piece == king && possibleCastling(to))
            {
                auto r = (to.x == Traits::Horizontal::G) ? rook[1] : rook[0];
                Traits::Coordinates coor = { (to.x == Traits::Horizontal::G) ? Traits::Horizontal::F : Traits::Horizontal::D, to.y };

                r->setCoordinates(coor);
                board->setPiece(r, coor);            
            }
            piece->setCoordinates(to);
            board->setPiece(piece, to);
        } 
    }
}