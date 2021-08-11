//
// Created by Sirzh on 15.04.2021.
//

#include "Piece.h"
#include "..\Player.h"


Piece::~Piece() = default;

Piece::Piece(const Player* p, Traits::Color c, Square* sqr)
: player(p)
, color(p->getColor())
, currentSqr(sqr)
{ }