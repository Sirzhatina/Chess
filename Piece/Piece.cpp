//
// Created by Sirzh on 15.04.2021.
//

#include <stdexcept>
#include <cstdlib>
#include "Piece.h"
#include "..\Player.h"
#include "..\Square.h"
#include "Board.h"

std::string Piece::errMsg = "Impossible to move";

Piece::Piece(const Player* p, Traits::Coordinates coord)
: player(p)
, color(p->getColor())
, currentCoord(coord)
{ }


bool Pawn::possibleMove(Traits::Coordinates to)
{
    auto from = getCoord();
    if (getPlayer()->getBoard()->getPiece(to) != nullptr)
    {
        if (getColor() != Traits::Color::WHITE && whiteAttack(from, to) ||
            getColor() != Traits::Color::BLACK && blackAttack(from, to) ||
            !whiteAttack(from, to) && !blackAttack(from, to))
        {
            return false;
        }
    }
    else if (firstMove && int(to.v) - int(from.v) > std::abs(2) ||
            int(to.v) - int(from.v) > std::abs(1)               ||
            to.h != from.h)
    {
        return false;
    }
    firstMove = false;
    return true;
}

bool Knight::possibleMove(Coordinates to)
{
    auto from = getCoord();
    if (!(int(from.v) - int(to.v) == std::abs(2) && int(from.h) - int(to.h) == std::abs(1)) ||
        !(int(from.h) - int(to.h) == std::abs(2) && int(from.v) - int(to.v) == std::abs(1)))
    {
        return false;
    }

    return true;
}

bool Bishop::possibleMove(Coordinates to)
{
    auto from = getCoord();
    if (std::abs(int(to.h) - int(from.h)) != std::abs(int(to.v) - int(from.v)))
    {
        return false;
    }

    return true;
}

bool Rook::possibleMove(Coordinates to)
{
    auto from = getCoord();
    if (from.h != to.h && from.v != to.v)
    {
        return false;
    }

    return true;
}

bool Queen::possibleMove(Coordinates to)
{
    auto from = getCoord();
    if (from.h != to.h && from.v != to.v ||
        std::abs(int(to.h) - int(from.h)) != std::abs(int(to.v) - int(from.v)))
    {
        return false;
    }
    return true;
}


bool King::possibleMove(Coordinates to)
{
    auto from = getCoord();
    if (std::abs(int(to.h) - int(from.h)) > 1 || std::abs(int(to.v) - int(from.v)) > 1)
    {
        return false;
    }
    return true;
}