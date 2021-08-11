#pragma once

#include "Traits.h"
#include "Square.h"
#include "Piece/Piece.h"
#include "Player.h"
#include "Board.h"


class Gameplay
{
    Board board;
    Player white{ &board, Traits::Color::WHITE };
    Player black{ &board, Traits::Color::BLACK };

    bool whiteMove{ true };

    bool isPossibleMove(Piece* who, Traits::Coordinates from, Traits::Coordinates to) const;
public:
    Gameplay() = default;

    bool showGoesOn() { return !white.isCheckmate() && !black.isCheckmate(); }

    int start();
};