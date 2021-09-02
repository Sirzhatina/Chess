#pragma once

#include <list>
#include "Traits.h"
#include "Piece/Piece.h"
#include "Player.h"
#include "Board.h"
#include "IObserver.h"

class Gameplay
{
    Board* board{ &Board::getInstance() };
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

    static Traits::Coordinates convertCoordinates(int x, int y) { return Traits::Coordinates{ Traits::Horizontal{ x }, Traits::Vertical{ y } }; }

    // implementing observer pattern
    std::list<IObserver*> observers;
    void Notify() const;

public:
    Gameplay() = default;
    ~Gameplay() = default;

    void addObserver(IObserver* ob) { observers.push_back(ob); }
    void removeObserver(IObserver* ob) { observers.remove(ob); }

    const Board* getBoard() const { return board; }

    int start();
};