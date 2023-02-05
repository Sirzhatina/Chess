#pragma once


#include <IDrawer.hpp>
#include <IInputHandler.hpp>
#include <memory>
#include "Player.hpp"
#include "Settings.hpp"
#include "Timer.hpp"

namespace Chess
{
class Board;

struct PlayerAttributes
{
    std::unique_ptr<Timer<std::chrono::seconds>> m_remainingTime;
    std::unique_ptr<Player> m_player;
};


class Gameplay
{
public:
    enum class Winner { white, black, stalemate };
    
public:
    Gameplay(std::shared_ptr<const IDrawer> drawer, std::shared_ptr<IInputHandler> input);
    ~Gameplay() = default;

    const Board& board() const { return *m_board; }

    Winner start();

    auto remainingTime(Color ofPlayer) const;

private:
    std::unique_ptr<Board>  m_board;
    
    PlayerAttributes m_white;
    PlayerAttributes m_black;

    bool stalemate{ false };
    bool checkmate{ false };

    std::shared_ptr<const IDrawer> m_drawer;
    std::shared_ptr<IInputHandler> m_input;

    void mainLoop(Player* moves, Player* notMoves);

    bool isStalemate(Player* moves, Player* notMoves);
    bool isEscapable(Player* moves, Player* notMoves);
};
} // ends namespace Chess