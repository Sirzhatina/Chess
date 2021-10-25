#pragma once

#include <list>
#include "Traits.h"
#include "Piece/Piece.h"
#include "Player.h"
#include "Board.h"
#include "IObserver.h"

namespace Chess
{
class Gameplay
{
    Board* board{ &Board::getInstance() };
    Player white{ board, Color::WHITE };
    Player black{ board, Color::BLACK };

    bool whiteMove{ true };
    bool stalemate{ false };

    // implementing observer pattern
    std::list<IObserver*> observers;
    void Notify() const;

    bool showGoesOn() const { return !white.isCheckmate() && !black.isCheckmate(); }
    void inputToMove(Coordinates& from, Coordinates& to) const;

    bool possibleMove(Player* moves, Player* checks, Coordinates from, Coordinates to) const;
    bool isCheckmate(Player* checks, Player* inCheck) const;

    void movingProccess(Coordinates from, Coordinates to);

    std::vector<Coordinates> allSquaresForKing(const Player* moves, const Player* notMoves) const;
    bool kingCanMove(const Player* moves, const Player* notMoves) const;

    static Coordinates convertCoordinates(int x, int y) { return Coordinates{ Horizontal{ x }, Vertical{ y }}; }

    void endgame() const;
    std::string winMessage() const { return "Congrats, " + std::string(white.isCheckmate() ? "black" : "white") + " player wins."; }
    static constexpr char drawMessage[] = "Oops, it seems to be draw.";

    class ExitExcep : public std::exception { 
    public:
        explicit ExitExcep(char* byeMsg): std::exception(byeMsg) { }
    };

    static constexpr char defaultLogFile[] = "logs.txt";
    static constexpr char quitCommand[] = "quit";

public:
    Gameplay() = default;
    ~Gameplay() = default;

    void addObserver(IObserver* ob) { observers.push_back(ob); }
    void removeObserver(IObserver* ob) { observers.remove(ob); }

    const Board* getBoard() const { return board; }

    int start();
};
} // ends namespace Chess