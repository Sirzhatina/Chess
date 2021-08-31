//
// Created by Sirzh on 15.04.2021.
//

#include <stdexcept>
#include <cstdlib>
#include "Piece.h"
#include "..\Player.h"
#include "Board.h"

std::string Piece::errMsg = "Impossible to move";

Piece::Piece(const Player* p, Traits::Coordinates coord)
: player(p)
, board(p->getBoard())
, color(p->getColor())
, currentCoord(coord)
{ }

void Piece::setCoordinates(Traits::Coordinates to)
{
    firstMove = false;
    currentCoord = to;
}

bool Pawn::possibleAttack(Traits::Coordinates to) const 
{
    int move = int(to.y) - int(getCoord().y);
    auto piece = getBoard()->getPiece(to);

    return (getColor() == Traits::Color::BLACK ? move == -1 : move == 1) && 
            std::abs(int(to.x) - int(getCoord().x)) == 1                 && 
            piece != nullptr                                             &&
            piece->getColor() != getColor(); 
}

bool Pawn::correctRoute(const Pawn& p, Traits::Coordinates to)
{
    int move = int(to.y) - int(p.getCoord().y);
    bool correctDirection = (move > 0) ? p.getColor() == Traits::Color::WHITE : p.getColor() == Traits::Color::BLACK;
    if (std::abs(move) <= p.isFirstMove() ? 2 : 1 && 
         to.x == p.getCoord().x                   &&
         correctDirection                         &&
         p.getBoard()->getPiece(to) == nullptr)
    {
        if (std::abs(move) == 2)
        {
            Traits::Coordinates coor{ to.x, (move > 0) ? Traits::Vertical{ int(to.y) - 1 } : Traits::Vertical{ int(to.y) + 1 } };
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

bool Knight::correctRoute(Traits::Coordinates from, Traits::Coordinates to, const Board* b)
{
    if ((std::abs(int(to.y) - int(from.y)) == 2 && std::abs(int(to.x) - int(from.x)) == 1) ||
        (std::abs(int(to.x) - int(from.x)) == 2 && std::abs(int(to.y) - int(from.y)) == 1))
    {
        return true;
    }
    return false;
}

bool Bishop::correctRoute(Traits::Coordinates from, Traits::Coordinates to, const Board* b)
{
    int diffX = int(to.x) - int(from.x);
    int diffY = int(to.y) - int(from.y);

    if (std::abs(diffX) != std::abs(diffY))
    {
        return false;
    }
    int incX = (diffX > 0) ? 1 : -1;
    int incY = (diffY > 0) ? 1 : -1;

    for (auto coor = from; coor != to; )
    {
        coor.x = Traits::Horizontal(int(coor.x) + incX); 
        coor.y = Traits::Vertical(int(coor.y) + incY);
        if (b->getPiece(coor) != nullptr)
        {
            return false;
        }
    }
    return true;
}

std::vector<Traits::Coordinates> Bishop::squaresBefore(Traits::Coordinates to) const
{
    int diffX = int(to.x) - int(getCoord().x);
    int diffY = int(to.y) - int(getCoord().y);

    std::vector<Traits::Coordinates> result{ getCoord() };

    if (std::abs(diffX) == std::abs(diffY))
    {
        int incX = (diffX > 0) ? 1 : -1;
        int incY = (diffY > 0) ? 1 : -1;

        auto coor = getCoord();
        coor.x = Traits::Horizontal(int(coor.x) + incX); 
        coor.y = Traits::Vertical(int(coor.y) + incY);
        while (coor != to)
        {
            result.push_back(coor);

            coor.x = Traits::Horizontal(int(coor.x) + incX); 
            coor.y = Traits::Vertical(int(coor.y) + incY);
        }
    }
    return result;
}

bool Rook::correctRoute(Traits::Coordinates from, Traits::Coordinates to, const Board* b)
{
    if (from.x != to.x && from.y != to.y)
    {
        return false;
    }

    if (from.x != to.x)
    {
        int incX = int(to.x) - int(from.x) > 0 ? 1 : -1;
        for (auto coor = from; coor != to; )
        {
            coor.x = Traits::Horizontal(int(coor.x) + incX);
            if (b->getPiece(coor) != nullptr)
            {
                return false;
            }
        }
    }
    else
    {
        int incY = int(to.y) - int(from.y) > 0 ? 1 : -1;
        for (auto coor = from; coor != to; )
        {
            coor.y = Traits::Vertical(int(coor.y) + incY);
            if (b->getPiece(to) != nullptr)
            {
                return false;
            }
        }
    }
    return true;
}

std::vector<Traits::Coordinates> Rook::squaresBefore(Traits::Coordinates to) const
{
    std::vector<Traits::Coordinates> result{ getCoord() };

    if (!(getCoord().x != to.x && getCoord().y != to.y))
    {
        auto coor = getCoord();
        if (getCoord().x != to.x)
        {
            int incX = int(to.x) - int(getCoord().x) > 0 ? 1 : -1;

            coor.x = Traits::Horizontal(int(coor.x) + incX);
            while (coor != to)
            {
                result.push_back(coor);
                coor.x = Traits::Horizontal(int(coor.x) + incX);
            }
        }
        else
        {
            int incY = int(to.y) - int(getCoord().y) > 0 ? 1 : -1;

            coor.y = Traits::Vertical(int(coor.y) + incY);
            while (coor != to)
            {
                result.push_back(coor);
                coor.y = Traits::Vertical(int(coor.y) + incY);
            }
        }
    }
    return result;
}

bool Queen::correctRoute(Traits::Coordinates from, Traits::Coordinates to, const Board* b)
{
    return Bishop::correctRoute(from, to, b) || Rook::correctRoute(from, to, b);
}

std::vector<Traits::Coordinates> Queen::squaresBefore(Traits::Coordinates to) const
{
    std::vector<Traits::Coordinates> result{ getCoord() };

    int diffX = int(to.x) - int(getCoord().x);
    int diffY = int(to.y) - int(getCoord().y);

    auto coor = getCoord();
    if (std::abs(diffX) == std::abs(diffY))
    {
        int incX = (diffX > 0) ? 1 : -1;
        int incY = (diffY > 0) ? 1 : -1;

        coor.x = Traits::Horizontal(int(coor.x) + incX); 
        coor.y = Traits::Vertical(int(coor.y) + incY);
        while (coor != to)
        {
            result.push_back(coor);
            coor.x = Traits::Horizontal(int(coor.x) + incX); 
            coor.y = Traits::Vertical(int(coor.y) + incY);
        }
    }
    else if (!(getCoord().x != to.x && getCoord().y != to.y))
    {
        if (getCoord().x != to.x)
        {
            int incX = int(to.x) - int(getCoord().x) > 0 ? 1 : -1;
            coor.x = Traits::Horizontal(int(coor.x) + incX);
            while (coor != to)
            {
                result.push_back(coor);
                coor.x = Traits::Horizontal(int(coor.x) + incX);
            }
        }
        else
        {
            int incY = int(to.y) - int(getCoord().y) > 0 ? 1 : -1;
            coor.y = Traits::Vertical(int(coor.y) + incY);
            while (coor != to)
            {
                result.push_back(coor);
                coor.y = Traits::Vertical(int(coor.y) + incY);
            }
        }
    }
    return result;
}

bool King::correctRoute(const King& k, Traits::Coordinates from, Traits::Coordinates to)
{
    if (std::abs(int(to.x) - int(from.x)) > 1 || std::abs(int(to.y) - int(from.y)) > 1)
    {
        return false;
    }
    return true;
}