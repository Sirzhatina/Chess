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
    Player m_player;
    Timer<std::chrono::seconds> m_timer;

    bool m_isInCheck{false};
};


class Match
{
public:
    enum class Winner { white, black, stalemate };
    
public:
    Match(std::shared_ptr<const IDrawer> drawer, std::shared_ptr<IInputHandler> input);
    ~Match() = default;

    const Board& board() const { return *m_board; }

    Winner start();

    auto remainingTime(Color ofPlayer) const;

private:
    std::unique_ptr<Board>  m_board;
    
    std::unique_ptr<PlayerAttributes> m_white;
    std::unique_ptr<PlayerAttributes> m_black;

    bool stalemate{ false };
    bool checkmate{ false };
    bool expired{false};

    Settings::Match m_matchAlias{Settings::instance().m_mSettings};

    std::shared_ptr<const IDrawer> m_drawer;
    std::shared_ptr<IInputHandler> m_input;

    void waitForInput(std::future<Move>& f, auto& timer);

    void mainLoop(PlayerAttributes* moves, PlayerAttributes* notMoves);

    void completeMove(PlayerAttributes* moves, PlayerAttributes* notMoves);

    bool isStalemate(PlayerAttributes* moves, PlayerAttributes* notMoves);
    bool isEscapable(PlayerAttributes* moves, PlayerAttributes* notMoves);
};
} // ends namespace Chess