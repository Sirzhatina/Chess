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
    void inputToMove(Traits::Coordinates& from, Traits::Coordinates& to) const;

    bool possibleMove(const Player* moves, const Player* checks, Traits::Coordinates from, Traits::Coordinates to) const;
    
    static Traits::Coordinates convertCoordinates(int x, int y) { return { Traits::Horizontal{ x }, Traits::Vertical{ y } }; }

public:
    Gameplay() = default;

    int start();
};