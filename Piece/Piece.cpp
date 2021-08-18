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


bool Pawn::possibleMove(Traits::Coordinates to) const
{
    auto from = getCoord();

    if (firstMove && int(to.y) - int(from.y) > std::abs(2) ||
        !firstMove && int(to.y) - int(from.y) > std::abs(1) ||
        to.x != from.x)
    {
        if (!possibleAttack(to))
        {
            return false;
        }
    }
    return true;
}

bool Pawn::possibleAttack(Coordinates to) const 
{
    auto from = getCoord();
    int move = int(to.y) - int(from.y);
    return (getColor() == Traits::Color::BLACK ? move == -1 : move == 1) && 
                                 std::abs(int(to.x) - int(from.x)) == 1  && 
                                    getBoard()->getPiece(to) != nullptr; 
}

bool Knight::possibleMove(Coordinates to) const
{
    auto from = getCoord();
    if (!(std::abs(int(from.y) - int(to.y)) == 2 && std::abs(int(from.x) - int(to.x)) == 1) ||
        !(std::abs(int(from.x) - int(to.x)) == 2 && std::abs(int(from.y) - int(to.y)) == 1))
    {
        return false;
    }

    return true;
}

bool Bishop::possibleMove(Coordinates to) const
{
    auto from = getCoord();
    if (std::abs(int(to.x) - int(from.x)) != std::abs(int(to.y) - int(from.y)))
    {
        return false;
    }

    return true;
}

bool Rook::possibleMove(Coordinates to) const
{
    auto from = getCoord();
    if (from.x != to.x && from.y != to.y)
    {
        return false;
    }

    return true;
}

bool Queen::possibleMove(Coordinates to) const
{
    auto from = getCoord();
    if (from.x != to.x && from.x != to.x ||
        std::abs(int(to.x) - int(from.x)) != std::abs(int(to.y) - int(from.y)))
    {
        return false;
    }
    return true;
}


bool King::possibleMove(Coordinates to) const
{
    auto from = getCoord();
    if (std::abs(int(to.x) - int(from.x)) > 1 || std::abs(int(to.y) - int(from.y)) > 1)
    {
        return false;
    }
    return true;
}