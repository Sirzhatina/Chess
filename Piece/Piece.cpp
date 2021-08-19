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
    if (firstMove && int(to.y) - int(getCoord().y) > std::abs(2) ||
        !firstMove && int(to.y) - int(getCoord().y) > std::abs(1) ||
        to.x != getCoord().x)
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
    int move = int(to.y) - int(getCoord().y);
    return (getColor() == Traits::Color::BLACK ? move == -1 : move == 1) && 
                                 std::abs(int(to.x) - int(getCoord().x)) == 1  && 
                                    getBoard()->getPiece(to) != nullptr; 
}

bool Knight::possibleMove(Coordinates to) const
{
    if (!(std::abs(int(getCoord().y) - int(to.y)) == 2 && std::abs(int(getCoord().x) - int(to.x)) == 1) ||
        !(std::abs(int(getCoord().x) - int(to.x)) == 2 && std::abs(int(getCoord().y) - int(to.y)) == 1))
    {
        return false;
    }

    return true;
}

bool Bishop::possibleMove(Traits::Coordinates to) const
{
    int diffX = int(to.x) - int(getCoord().x);
    int diffY = int(to.y) - int(getCoord().y);

    if (std::abs(diffX) != std::abs(diffY))
    {
        return false;
    }
    int incX = diffX > 0 ? 1 : -1;
    int incY = diffY > 0 ? 1 : -1;

    for (Traits::Coordinates coor = getCoord(); coor != to; diffX += incX, diffY += diffY)
    {
        
    }

    return true;
}

bool Rook::possibleMove(Coordinates to) const
{
    if (getCoord().x != to.x && getCoord().y != to.y)
    {
        return false;
    }

    return true;
}

bool Queen::possibleMove(Coordinates to) const
{
    if (getCoord().x != to.x && getCoord().y != to.y &&
        std::abs(int(to.x) - int(getCoord().x)) != std::abs(int(to.y) - int(getCoord().y)))
    {
        return false;
    }
    return true;
}


bool King::possibleMove(Coordinates to) const
{
    if (std::abs(int(to.x) - int(getCoord().x)) > 1 || std::abs(int(to.y) - int(getCoord().y)) > 1)
    {
        return false;
    }
    return true;
}