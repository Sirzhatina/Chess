//
// Created by Sirzh on 15.04.2021.
//

#include "Piece.h"


Piece::Piece(const Player* p, Traits::Color c, Square* sqr)
: player(p)
, currentSqr(sqr)
{ }


void Pawn::move(Traits::Coordinates to)
{
    if (firstMove)
    {
        
    }
}