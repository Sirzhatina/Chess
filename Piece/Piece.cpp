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
, board(player->getBoard())
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
    else if (firstMove && int(to.y) - int(from.y) > std::abs(2) ||
            int(to.y) - int(from.y) > std::abs(1)               ||
            to.x != from.x)
    {
        return false;
    }
    firstMove = false;
    return true;
}

bool Knight::possibleMove(Coordinates to)
{
    auto from = getCoord();
    if (!(std::abs(int(from.y) - int(to.y)) == 2 && std::abs(int(from.x) - int(to.x)) == 1) ||
        !(std::abs(int(from.x) - int(to.x)) == 2 && std::abs(int(from.y) - int(to.y)) == 1))
    {
        return false;
    }

    return true;
}

bool Bishop::possibleMove(Coordinates to)
{
    auto from = getCoord();
    if (std::abs(int(to.x) - int(from.x)) != std::abs(int(to.y) - int(from.y)))
    {
        return false;
    }

    return true;
}

bool Rook::possibleMove(Coordinates to)
{
    auto from = getCoord();
    if (from.x != to.x && from.y != to.y)
    {
        return false;
    }

    return true;
}

bool Queen::possibleMove(Coordinates to)
{
    auto from = getCoord();
    if (from.x != to.x && from.x != to.x ||
        std::abs(int(to.x) - int(from.x)) != std::abs(int(to.y) - int(from.y)))
    {
        return false;
    }
    return true;
}


bool King::possibleMove(Coordinates to)
{
    auto from = getCoord();
    if (std::abs(int(to.x) - int(from.x)) > 1 || std::abs(int(to.y) - int(from.y)) > 1)
    {
        return false;
    }
    return true;
}