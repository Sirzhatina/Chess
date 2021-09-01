#pragma once

#include "Traits.h"
#include "Piece/Piece.h"
#include "Player.h"
#include "Board.h"


class Gameplay
{
    Board* board;
    Player white{ board, Traits::Color::WHITE };
    Player black{ board, Traits::Color::BLACK };

    bool whiteMove{ true };
    bool stalemate{ false };

    bool showGoesOn() const { return !white.isCheckmate() && !black.isCheckmate(); }
    void inputToMove(Traits::Coordinates& from, Traits::Coordinates& to) const;

    bool possibleMove(Player* moves, Player* checks, Traits::Coordinates from, Traits::Coordinates to) const;
    bool isCheckmate(Player* checks, Player* inCheck) const;

    void endgame() const;
    void movingProccess(Traits::Coordinates from, Traits::Coordinates to);

    std::vector<Traits::Coordinates> allSquaresForKing(const Player* moves, const Player* notMoves) const;
    bool kingCanMove(const Player* moves, const Player* notMoves) const;

    static Traits::Coordinates convertCoordinates(int x, int y) { return { Traits::Horizontal{ x }, Traits::Vertical{ y } }; }

public:
    Gameplay(Board* b);

    int start();
};