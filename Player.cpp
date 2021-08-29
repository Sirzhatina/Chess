//
// Created by Sirzh on 15.04.2021.
//

#include "Player.h"
#include "Piece\Piece.h"
#include "Board.h"
#include <stdexcept>


Player::Player(Board* b, Traits::Color c)
: board(b)
, color(c)
{
    if (b == nullptr)
    {
        throw std::runtime_error{ "Cannot create player without board" };
    }
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

void Player::castling(Traits::Coordinates to)
{
    board->setPiece(king, to);
    king->setCoordinates(to);

    auto rk = (to.x == Traits::Horizontal::C) ? rook[0] : rook[1];
    Traits::Coordinates rkDest{ (rk == rook[0]) ? Traits::Horizontal::D : Traits::Horizontal::F, to.y };

    board->setPiece(rk, rkDest);
    rk->setCoordinates(rkDest);
}

std::vector<Piece*> Player::accessToSquare(Traits::Coordinates to) const
{
    std::vector<Piece*> result;
    for (auto p : pawn)
    {
        if (p->possibleMove(to))
        {
            result.push_back(p);
        }
    }
    Piece* pieces[8] { rook[0], rook[1], knight[0], knight[1], bishop[0], bishop[1], queen, king };
    for (auto p : pieces)
    {
        if (p->possibleMove(to))
        {
            result.push_back(p);
        }
    }
    return result;
}

Piece* Player::move(Traits::Coordinates from, Traits::Coordinates to)
{
    auto piece = const_cast<Piece*>(board->getPiece(from));
    if (isOwner(piece) && !friendlySquare(to))
    {
        if (piece == king && possibleCastling(to))
        {
            castling(to); 
        }
        else if (piece->possibleMove(to))
        {
            piece->setCoordinates(to);
            return board->setPiece(piece, to);
        }
        else
        {
            throw std::runtime_error{ "Impossible to move" };
        }
    }
    return nullptr;
}