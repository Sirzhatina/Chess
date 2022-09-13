//
// Created by Sirzh on 15.04.2021.
//

#include "Player.hpp"
#include "Piece\Piece.hpp"
#include "Board.hpp"
#include <stdexcept>

namespace Chess
{
Player::Player(Board* b, Color c)
: _board(b)
, _color(c)
{
    if (b == nullptr)
    {
        throw std::runtime_error{ "Error! Please, pass the board to the Player" };
    }
    _board->addPlayer(this);

    auto initPawns = [this]()
    {
        auto startY = (_color == Color::WHITE) ? Vertical::two : Vertical::seven;

        for (int startX = 0; startX < pawns; startX++)
        {
            _pieces[startX] = std::make_unique<Pawn>(this, Coordinates{ Horizontal(startX), startY });
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
            _pieces[i] = std::make_unique<Rook>(this, Coordinates{ Horizontal{ startX += inc }, startY });
            _board->setPiece(_pieces[i].get(), _pieces[i]->coord());
            i++;

            _pieces[i] = std::make_unique<Knight>(this, Coordinates{ Horizontal{ startX += inc }, startY });
            _board->setPiece(_pieces[i].get(), _pieces[i]->coord());
            i++;

            _pieces[i] = std::make_unique<Bishop>(this, Coordinates{ Horizontal{ startX += inc }, startY });
            _board->setPiece(_pieces[i].get(), _pieces[i]->coord());
            i++;

            inc *= -1;
            startX += 6;
        }
        leftRook  = _pieces[8].get();
        rightRook = _pieces[11].get();

        _pieces[allPiecesExceptKing - 1] = std::make_unique<Queen>(this, Coordinates{ Horizontal::D, startY });
        _board->setPiece(_pieces[allPiecesExceptKing - 1].get(), _pieces[allPiecesExceptKing - 1]->coord());

        _king = std::make_unique<King>(this, Coordinates{ Horizontal::E, startY });
        _board->setPiece(_king.get(), _king->coord()); 
    };

    initPawns();
    initOthers();
}

bool Player::isValidMove(Move m) const
{
    auto findPiece = [this](const Piece* p) -> Piece*
    {
        for (const auto& piece : _pieces)
        {
            if (p == piece.get())
            {
                return piece.get();
            }
        }
        return p == _king.get() ? _king.get() : nullptr;
    };

    auto isInCheck = [this](Move m)
    {
        // auto previous = _board->setPiece(_board->setPiece(nullptr, m.from), m.to);
        // _board->setPiece(_board->setPiece(previous, m.to), m.from);

        auto previous = _board->getPiece(m.to);

        auto attackingPieces = _board->enemyOf(this)->piecesAccessingSquare(_king->coord());

        for (const auto& p : attackingPieces)
        {
            if (p != previous)
            {
                return true;
            }
        }
        return false;
    };

    auto isValidCastling = [this](const Piece* p, Coordinates to)
    {
        if (_isCastled)
        {
            return false;
        }
        auto enemy = board()->enemyOf(this);
        if (p == _king.get() && _king->isFirstMove() && to.y == _king->coord().y)
        {
            bool isAccessed = enemy->isAccessibleSquare({ Horizontal::E, _king->coord().y });
            if (to.x == Horizontal::G)
            {
                isAccessed &= enemy->isAccessibleSquare({ Horizontal::F, _king->coord().y });
                return rightRook->isFirstMove() && rightRook->isPossibleMove({ Horizontal::F, to.y }) && !isAccessed;
            }
            if (to.x == Horizontal::C)
            {
                isAccessed &= enemy->isAccessibleSquare({ Horizontal::D, _king->coord().y });
                return leftRook->isFirstMove() && leftRook->isPossibleMove({ Horizontal::D, to.y }) && !isAccessed;
            }
        }
        return false;
    };    

    auto piece = findPiece(_board->getPiece(m.from));

    if (isInCheck(m))
    {
        return false;
    }
    if (piece && piece->isPossibleMove(m.to))
    {
        _validatedMove = m;
    }
    if (!_validatedMove.has_value())
    {
        if (isValidCastling(piece, m.to))
        {
            _validatedCastling = m;
        }
    }

    return _validatedMove.has_value() || _validatedCastling.has_value();
}

std::optional<const Piece*> Player::move()
{
    Move alias;
    if (_validatedMove.has_value())
    {
        alias = _validatedMove.value();
        auto kicked = _board->setPiece(_board->setPiece(nullptr, alias.from), alias.to);

        if (_board->getPiece(alias.from))
        {
            const_cast<Piece*>(_board->getPiece(alias.from))->setCoordinates(alias.to);
        }
        _validatedMove = { };

        return { kicked };
    }
    if (_validatedCastling.has_value())
    {
        alias = _validatedCastling.value();
        _isCastled = true;

        auto rook = (alias.to.x == Horizontal::C) ? leftRook : rightRook;
        Coordinates rkDest{ (rook == leftRook) ? Horizontal::D : Horizontal::F, alias.to.y };

        _board->setPiece(_board->setPiece(nullptr, _king->coord()), alias.to);
        _king->setCoordinates(alias.to);

        _board->setPiece(_board->setPiece(nullptr, rook->coord()), rkDest);
        const_cast<Piece*>(rook)->setCoordinates(rkDest);

        _validatedCastling = { };

        return { nullptr };
    }
    return { };
}

std::vector<const Piece*> Player::piecesAccessingSquare(Coordinates to) const
{
    std::vector<const Piece*> result;
    for (const auto& piece : _pieces)
    {
        if (piece && piece->isPossibleMove(to))
        {
            result.push_back(piece.get());
        }
    }
    return result;
}

bool Player::isAccessibleSquare(Coordinates to) const
{
    for (const auto& piece : _pieces)
    {
        if (piece && piece->isPossibleMove(to))
        {
            return true;
        }
    }
    return false;
}

std::vector<const Piece*> Player::piecesAbleToMove() const
{
    std::vector<const Piece*> result;
    
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
                        result.push_back(_pieces[i].get());
                    }
                }
            }
        }
    }
    for (int i = pawns; i < allPiecesExceptKing; i++)
    {
        if (_pieces[i])
        {
            result.push_back(_pieces[i].get());
        }
    }
    return result;
}

bool Player::isMovableKing() const
{
    Coordinates coord;
    for (int x = int(_king->coord().x) - 1, lim = x + 3; x < lim; x++)
    {
        for (int y = int(_king->coord().y) - 1, lim = y + 3; y < lim; y++)
        {
            if (x > 0 && x < boardSize && y > 0 && y < boardSize)
            {
                coord = { Horizontal{x}, Vertical{y} };
                if (_king->isPossibleMove(coord))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

std::vector<Coordinates> Player::kingsAccessibleSquares() const
{
    std::vector<Coordinates> result;
    Coordinates coord;
    for (int x = int(_king->coord().x) - 1, lim = x + 3; x < lim; x++)
    {
        for (int y = int(_king->coord().y) - 1, lim = y + 3; y < lim; y++)
        {
            if (x > 0 && x < boardSize && y > 0 && y < boardSize)
            {
                coord = { Horizontal{x}, Vertical{y} };
                if (_king->isPossibleMove(coord))
                {
                    result.push_back(coord);
                }
            }
        }
    }
    return result;
}

void Player::removePiece(const Piece* p)
{
    if (p)
    {
        for (auto& piece : _pieces)
        {
            if (p == piece.get())
            {
                piece.release();
                return;
            }
        }
    }

}

bool Player::isMovablePawns() const
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
}

bool Player::isMovableOthers() const
{
    for (int i = pawns; i < allPiecesExceptKing; i++)
    {
        if (_pieces[i])
        {
            return true;
        }
    }
    return false;
}

bool Player::isAbleToMove() const
{
    return isMovableOthers() || isMovablePawns();
}

} // ends namespace Chess