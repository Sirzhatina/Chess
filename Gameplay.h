#pragma once

#include <list>
#include <utility>
#include "Primitives.h"
#include "Piece/Piece.h"
#include "Player.h"
#include "Board.h"
#include "IObserver.h"

namespace Chess
{
typedef std::pair<Coordinates, Coordinates> (*inputHandler)();

class Gameplay
{
public:
    Gameplay(inputHandler getMove);
    ~Gameplay() = default;

    const Board* board() const { return _board.get(); }

    Color start();

private:
    std::unique_ptr<Board>  _board;
    std::unique_ptr<Player> _white;
    std::unique_ptr<Player> _black;

    bool whiteMove{ true };

    bool stalemate{ false };
    bool checkmate{ false };

    inputHandler _getMove;
};
} // ends namespace Chess