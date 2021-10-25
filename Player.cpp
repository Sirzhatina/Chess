//
// Created by Sirzh on 15.04.2021.
//

#include "Player.h"
#include "Piece\Piece.h"
#include "Board.h"
#include <stdexcept>

namespace Chess
{
Player::Player(Board* b, Color c)
: board(b)
, color(c)
{
    if (b == nullptr)
    {
        throw std::runtime_error{ "Cannot create player without board" };
    }
    board->addPlayer(this);

    auto startOfPawns = (color == Color::WHITE) ? Vertical::two : Vertical::seven;
    auto startOfOthers = (color == Color::WHITE) ? Vertical::one : Vertical::eight;

    int alongLine = 0;
    for (auto& pwn: pawn)
    {
        pwn = new Pawn{ this, Coordinates{ Horizontal(alongLine++), startOfPawns } };
        board->setPiece(pwn, pwn->getCoord());
    }

    alongLine = -1;
    for (int i = 0, inc = 1; i < PAIR_PIECES; i++)
    {
        rook[i] = new Rook{ this, Coordinates{ Horizontal(alongLine += inc), startOfOthers } };
        board->setPiece(rook[i], rook[i]->getCoord());

        knight[i] = new Knight{ this, Coordinates{ Horizontal(alongLine += inc), startOfOthers } };
        board->setPiece(knight[i], knight[i]->getCoord());

        bishop[i] = new Bishop{ this, Coordinates{ Horizontal{ alongLine += inc }, startOfOthers } };
        board->setPiece(bishop[i], bishop[i]->getCoord());

        inc *= -1;
        alongLine += 6;
    }

    // Queen prefers corresponding color
    queen = new Queen{ this, { Horizontal::D, startOfOthers } };
    board->setPiece(queen, queen->getCoord());

    king = new King{ this, { Horizontal::E, startOfOthers } };
    board->setPiece(king, king->getCoord());
}

bool Player::possibleCastling(Coordinates to) const
{
    if (king->isFirstMove())
    {
        if (to.y == king->getCoord().y)
        {
            if (to.x == Horizontal::G)
            {
                if (getBoard()->getPiece({ Horizontal::F, to.y }) == nullptr &&
                    getBoard()->getPiece({ Horizontal::G, to.y }) == nullptr)
                {
                    return rook[1]->isFirstMove();
                }
            }
            else if (to.x == Horizontal::C)
            {
                if (getBoard()->getPiece({ Horizontal::D, to.y }) == nullptr &&
                    getBoard()->getPiece({ Horizontal::C, to.y }) == nullptr &&
                    getBoard()->getPiece({ Horizontal::B, to.y }) == nullptr)
                {
                    return rook[0]->isFirstMove();
                }
            }
        }
    }
    return false;
}

void Player::castling(Coordinates to)
{
    board->setPiece(board->setPiece(nullptr, king->getCoord()), to);
    king->setCoordinates(to);

    auto rk = (to.x == Horizontal::C) ? rook[0] : rook[1];
    Coordinates rkDest{ (rk == rook[0]) ? Horizontal::D : Horizontal::F, to.y };

    board->setPiece(board->setPiece(nullptr, rk->getCoord()), rkDest);
    rk->setCoordinates(rkDest);
}

std::vector<Piece*> Player::piecesAccessingSquare(Coordinates to) const
{
    std::vector<Piece*> result;
    for (auto p : pawn)
    {
        if (p->possibleMove(to))
        {
            result.push_back(p);
        }
    }
    Piece* pieces[7] { rook[0], rook[1], knight[0], knight[1], bishop[0], bishop[1], queen };
    for (auto p : pieces)
    {
        if (p->possibleMove(to))
        {
            result.push_back(p);
        }
    }
    return result;
}

bool Player::isAccessedSquare(Coordinates to) const
{
    for (const auto p : pawn)
    {
        if (p->possibleMove(to))
        {
            return true;
        }
    }
    if (rook[0]  ->possibleMove(to) || rook[1]  ->possibleMove(to) ||
        knight[0]->possibleMove(to) || knight[1]->possibleMove(to) ||
        bishop[0]->possibleMove(to) || bishop[1]->possibleMove(to) ||
        queen    ->possibleMove(to))
    {
        return true;
    }
    return false;
}

bool Player::isAbleToMove() const
{
    Piece* pieces[7]{ rook[0], rook[1], knight[0], knight[1], bishop[0], bishop[1], queen };

    for (const auto p : pieces)
    {
        if (p->getCoord() != NULLPOS)
        {
            return true;
        }
    }
    Coordinates sqrToMove;
    for (const auto p : pawn)
    {
        if (p->getCoord() != NULLPOS) 
        {
            sqrToMove.y = Vertical(int(p->getCoord().y) + (color == Color::WHITE) ? 1 : -1);

            for (int x = int(p->getCoord().x) - 1, lim = x + 3; x < lim; x++)
            {
                if (x > 0 && x < boardSize)
                {
                    sqrToMove.x = Horizontal{x};
                    if (sqrToMove != NULLPOS && p->possibleMove(sqrToMove))
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

Piece* Player::move(Coordinates from, Coordinates to)
{
    auto piece = const_cast<Piece*>(board->getPiece(from));

    auto isOwner = [this] (const Piece* p) { return p->getPlayer() == this; };
    if (isOwner(piece) && !friendlySquare(to))
    {
        if (piece == king && possibleCastling(to))
        {
            castling(to); 
        }
        else if (piece->possibleMove(to))
        {
            board->setPiece(nullptr, from);
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
} // ends namespace Chess