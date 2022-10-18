#pragma once

#include "IGameplayHandler.hpp"
#include <memory>
#include "Player.hpp"

namespace Chess
{
class Board;

class Gameplay
{
public:
    enum class Winner { white, black, stalemate };
    
public:
    Gameplay(std::shared_ptr<IGameplayHandler> observer);
    ~Gameplay() = default;

    std::shared_ptr<const Board> board() const { return _board; }

    Winner start();

private:
    std::shared_ptr<Board>  _board;
    std::unique_ptr<Player> _white;
    std::unique_ptr<Player> _black;

    bool stalemate{ false };
    bool checkmate{ false };

    std::shared_ptr<IGameplayHandler> _observer;

    void mainLoop(Player* moves, Player* notMoves);

    bool isStalemate(Player* moves, Player* notMoves);
    bool isEscapable(Player* moves, Player* notMoves);
};
} // ends namespace Chess