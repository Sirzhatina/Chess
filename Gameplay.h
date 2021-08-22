#pragma once

#include "Traits.h"
#include "Piece/Piece.h"
#include "Player.h"
#include "Board.h"


class Gameplay
{
    Board board;
    Player white{ &board, Traits::Color::WHITE };
    Player black{ &board, Traits::Color::BLACK };

    bool whiteMove{ true };

    bool showGoesOn() { return !white.isCheckmate() && !black.isCheckmate(); }
    static Traits::Coordinates convertCoordinates(int x, int y) { return Traits::Coordinates{ Traits::Horizontal{ x }, Traits::Vertical{ y } }; }
    void inputToMove(Traits::Coordinates& from, Traits::Coordinates& to) const;
public:
    Gameplay() = default;

    int start();
};