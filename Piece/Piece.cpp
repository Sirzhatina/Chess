//
// Created by Sirzh on 15.04.2021.
//

#include <stdexcept>
#include <cstdlib>
#include "Piece.h"
#include "..\Player.h"
#include "..\Board.h"
namespace Chess
{
Piece::Piece(const Player* p, Coordinates coord)
: player(p)
, board(p->getBoard())
, color(p->getColor())
, currentCoord(coord)
{ }

void Piece::setCoordinates(Coordinates to)
{
    firstMove = false;
    currentCoord = to;
}

bool Pawn::possibleAttack(Coordinates to) const 
{
    int move = int(to.y) - int(getCoord().y);
    auto piece = getBoard()->getPiece(to);

    return (getColor() == Color::BLACK ? move == -1 : move == 1) && 
            std::abs(int(to.x) - int(getCoord().x)) == 1                 && 
            piece != nullptr                                             &&
            piece->getColor() != getColor(); 
}

bool Pawn::correctRoute(const Pawn& p, Coordinates to)
{
    int move = int(to.y) - int(p.getCoord().y);
    bool correctDirection = (move > 0) ? p.getColor() == Color::WHITE : p.getColor() == Color::BLACK;
    if (std::abs(move) <= (p.isFirstMove() ? 2 : 1) && 
        to.x == p.getCoord().x                      &&
        correctDirection                            &&
        p.getBoard()->getPiece(to) == nullptr)
    {
        if (std::abs(move) == 2)
        {
            Coordinates coor{ to.x, (move > 0) ? Vertical{ int(to.y) - 1 } : Vertical{ int(to.y) + 1 } };
            if (p.getBoard()->getPiece(coor) == nullptr)
            {
                return true;
            }
        }
        else
        {
            return true;
        }
    }
    return false;
}

bool Knight::correctRoute(Coordinates from, Coordinates to, const Board* b)
{
    if ((std::abs(int(to.y) - int(from.y)) == 2 && std::abs(int(to.x) - int(from.x)) == 1) ||
        (std::abs(int(to.x) - int(from.x)) == 2 && std::abs(int(to.y) - int(from.y)) == 1))
    {
        return true;
    }
    return false;
}

bool Bishop::correctRoute(Coordinates from, Coordinates to, const Board* b)
{
    int diffX = int(to.x) - int(from.x);
    int diffY = int(to.y) - int(from.y);

    if (std::abs(diffX) != std::abs(diffY))
    {
        return false;
    }
    int incX = (diffX > 0) ? 1 : -1;
    int incY = (diffY > 0) ? 1 : -1;

    Coordinates coor{ Horizontal(int(from.x) + incX), Vertical(int(from.y) + incY) };
    while (coor != to)
    {
        if (b->getPiece(coor) != nullptr)
        {
            return false;
        }
        coor.x = Horizontal(int(coor.x) + incX); 
        coor.y = Vertical(int(coor.y) + incY);
    }
    return true;
}

std::vector<Coordinates> Bishop::squaresBefore(Coordinates to) const
{
    int diffX = int(to.x) - int(getCoord().x);
    int diffY = int(to.y) - int(getCoord().y);

    std::vector<Coordinates> result{ getCoord() };

    if (std::abs(diffX) == std::abs(diffY))
    {
        int incX = (diffX > 0) ? 1 : -1;
        int incY = (diffY > 0) ? 1 : -1;

        auto coor = getCoord();
        coor.x = Horizontal(int(coor.x) + incX); 
        coor.y = Vertical(int(coor.y) + incY);
        while (coor != to)
        {
            result.push_back(coor);

            coor.x = Horizontal(int(coor.x) + incX); 
            coor.y = Vertical(int(coor.y) + incY);
        }
    }
    return result;
}

bool Rook::correctRoute(Coordinates from, Coordinates to, const Board* b)
{
    if (from.x != to.x && from.y != to.y)
    {
        return false;
    }

    if (from.x != to.x)
    {
        int incX = int(to.x) - int(from.x) > 0 ? 1 : -1;
        Coordinates coor{ Horizontal(int(from.x) + incX), from.y };
        while (coor != to)
        {
            if (b->getPiece(coor) != nullptr)
            {
                return false;
            }
            coor.x = Horizontal(int(coor.x) + incX);
        }
    }
    else
    {
        int incY = int(to.y) - int(from.y) > 0 ? 1 : -1;
        Coordinates coor{ from.x, Vertical(int(from.y) + incY) };
        while (coor != to)
        {
            if (b->getPiece(coor) != nullptr)
            {
                return false;
            }
            coor.y = Vertical(int(coor.y) + incY);
        }
    }
    return true;
}

std::vector<Coordinates> Rook::squaresBefore(Coordinates to) const
{
    std::vector<Coordinates> result{ getCoord() };

    if (!(getCoord().x != to.x && getCoord().y != to.y))
    {
        auto coor = getCoord();
        if (getCoord().x != to.x)
        {
            int incX = int(to.x) - int(getCoord().x) > 0 ? 1 : -1;

            coor.x = Horizontal(int(coor.x) + incX);
            while (coor != to)
            {
                result.push_back(coor);
                coor.x = Horizontal(int(coor.x) + incX);
            }
        }
        else
        {
            int incY = int(to.y) - int(getCoord().y) > 0 ? 1 : -1;

            coor.y = Vertical(int(coor.y) + incY);
            while (coor != to)
            {
                result.push_back(coor);
                coor.y = Vertical(int(coor.y) + incY);
            }
        }
    }
    return result;
}

bool Queen::correctRoute(Coordinates from, Coordinates to, const Board* b)
{
    return Bishop::correctRoute(from, to, b) || Rook::correctRoute(from, to, b);
}

std::vector<Coordinates> Queen::squaresBefore(Coordinates to) const
{
    std::vector<Coordinates> result{ getCoord() };

    int diffX = int(to.x) - int(getCoord().x);
    int diffY = int(to.y) - int(getCoord().y);

    auto coor = getCoord();
    if (std::abs(diffX) == std::abs(diffY))
    {
        int incX = (diffX > 0) ? 1 : -1;
        int incY = (diffY > 0) ? 1 : -1;

        coor.x = Horizontal(int(coor.x) + incX); 
        coor.y = Vertical(int(coor.y) + incY);
        while (coor != to)
        {
            result.push_back(coor);
            coor.x = Horizontal(int(coor.x) + incX); 
            coor.y = Vertical(int(coor.y) + incY);
        }
    }
    else if (!(getCoord().x != to.x && getCoord().y != to.y))
    {
        if (getCoord().x != to.x)
        {
            int incX = int(to.x) - int(getCoord().x) > 0 ? 1 : -1;
            coor.x = Horizontal(int(coor.x) + incX);
            while (coor != to)
            {
                result.push_back(coor);
                coor.x = Horizontal(int(coor.x) + incX);
            }
        }
        else
        {
            int incY = int(to.y) - int(getCoord().y) > 0 ? 1 : -1;
            coor.y = Vertical(int(coor.y) + incY);
            while (coor != to)
            {
                result.push_back(coor);
                coor.y = Vertical(int(coor.y) + incY);
            }
        }
    }
    return result;
}

bool King::correctRoute(const King& k, Coordinates from, Coordinates to)
{
    if (std::abs(int(to.x) - int(from.x)) > 1 || std::abs(int(to.y) - int(from.y)) > 1)
    {
        return false;
    }
    return true;
}
} // namespace Chess