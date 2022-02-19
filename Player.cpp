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
: _board(b)
, _color(c)
{
    if (b == nullptr)
    {
        throw std::runtime_error{ "Cannot create player without _board" };
    }
    _board->addPlayer(this);

    auto initPawns = [this]()
    {
        auto startY = (_color == Color::WHITE) ? Vertical::two : Vertical::seven;

        for (int startX = 0; startX < pawns; startX++)
        {
            _pieces[startX] = std::make_shared<Pawn>(this, Coordinates{ Horizontal(startX++), startY });
            _board->setPiece(_pieces[startX].get(), _pieces[startX]->coord());        
        }
    };

    auto initOthers = [this]()
    {
        auto startY = (_color == Color::WHITE) ? Vertical::one : Vertical::eight;
        auto startX = -1;

        constexpr auto queen = 1;
        for (int i = pawns, inc = 1; i < allPiecesExceptKing - queen;)
        {
            _pieces[i] = std::make_shared<Rook>(this, Coordinates{ Horizontal{ startX += inc }, startY });
            _board->setPiece(_pieces[i].get(), _pieces[i]->coord());
            i++;

            _pieces[i] = std::make_shared<Knight>(this, Coordinates{ Horizontal{ startX += inc }, startY });
            _board->setPiece(_pieces[i].get(), _pieces[i]->coord());
            i++;

            _pieces[i] = std::make_shared<Bishop>(this, Coordinates{ Horizontal{ startX += inc }, startY });
            _board->setPiece(_pieces[i].get(), _pieces[i]->coord());
            i++;

            inc *= -1;
            startX += 6;
        }
        leftRook  = _pieces[8];
        rightRook = _pieces[11];

        _pieces[allPiecesExceptKing - 1] = std::make_shared<Queen>(this, Coordinates{ Horizontal::D, startY });
        _board->setPiece(_pieces[allPiecesExceptKing - 1].get(), _pieces[allPiecesExceptKing - 1]->coord());

        _king = std::make_shared<King>(this, Coordinates{ Horizontal::E, startY });
        _board->setPiece(_king.get(), _king->coord()); 
    };

    initPawns();
    initOthers();
}

std::vector<Piece*> Player::piecesAccessingSquare(Coordinates to) const
{
    std::vector<Piece*> result;
    for (auto piece : _pieces)
    {
        if (piece->isPossibleMove(to))
        {
            result.push_back(piece.get());
        }
    }
    return result;
}

bool Player::isAccessedSquare(Coordinates to) const
{
    for (const auto& piece : _pieces)
    {
        if (piece->isPossibleMove(to))
        {
            return true;
        }
    }
    return false;
}

bool Player::isAbleToMove() const
{
    auto isMovablePawns = [this]()
    {
        Coordinates sqrToMove;
        for (int i = 0, incY = (_color == Color::WHITE ? 1 : -1); i < pawns; i++)
        {
            if (_pieces[i])
            {
                sqrToMove.y = Vertical(int(_pieces[i]->coord().y) + incY);
                for (int x = int(_pieces[i]->coord().x) - 1, lim = x + 3; x < lim; x++)
                {
                    if (x > 0 && x < boardSize)
                    {
                        sqrToMove.x = Horizontal{x};
                        if (_pieces[i]->isPossibleMove(sqrToMove))
                        {
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    };

    auto isMovableOthers = [this]()
    {
        for (int i = pawns; i < allPiecesExceptKing; i++)
        {
            if (_pieces[i])
            {
                return true;
            }
        }
        return false;
    };
    return isMovableOthers() || isMovablePawns();
}

std::pair<bool, const Piece*> Player::tryMove(Coordinates from, Coordinates to)
{
    auto findPiece = [this](const Piece* p) -> Chess::Piece*
    {
        for (auto piece : _pieces)
        {
            if (piece.get() == p)
            {
                return piece.get();
            }
        }
        return nullptr;
    };

    auto isValidMove = [this, &findPiece](const Piece* p, Coordinates to)
    {
        if (findPiece(p))
        {
            return p->isPossibleMove(to);
        }
        return false;
    };
    auto move = [this](Piece* p, Coordinates to)
    {
        auto kicked = _board->setPiece(p, to);
        p->setCoordinates(to);

        return kicked;
    };

    auto isValidCastling = [this](Coordinates to)
    {
        if (_king->isFirstMove() && to.y == _king->coord().y)
        {
            if (to.x == Horizontal::G)
            {
                return rightRook->isFirstMove() && rightRook->isPossibleMove({ Horizontal::F, to.y });
            }
            if (to.x == Horizontal::C)
            {
                return leftRook->isFirstMove() && leftRook->isPossibleMove({ Horizontal::D, to.y });
            }
        }
        return false;
    };
    auto castling = [this, &move](Coordinates to)
    {
        auto rook = (to.x == Horizontal::C) ? leftRook : rightRook;
        Coordinates rkDest{ (rook == leftRook) ? Horizontal::D : Horizontal::F, to.y };

        move(_king.get(), to);
        move(rook.get(), rkDest);
    };

    auto piece = findPiece(_board->getPiece(from));
    if (isValidMove(piece, to))
    {
        return { true, move(piece, to) };
    }
    if (isValidCastling(to))
    {
        castling(to);
        return { true, nullptr };
    }

    return { false, nullptr };
}
} // ends namespace Chess