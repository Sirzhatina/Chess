#include "Match.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include <vector>
#include <cstdlib>
#include <iostream>

namespace Chess
{

Match::Match(std::shared_ptr<const IDrawer> drawer, std::shared_ptr<IInputHandler> input): m_drawer(drawer), m_input(input)
{
    m_board = std::make_unique<Board>();
    m_white.reset(new PlayerAttributes(Player(m_board.get(), Color::WHITE)));
    m_black.reset(new PlayerAttributes(Player(m_board.get(), Color::BLACK)));

    if (m_matchAlias.tm != Settings::Match::Time::no_time)
    {
        auto mins = std::chrono::minutes(int(Settings::instance().m_mSettings.tm));

        m_white->m_timer = Timer<std::chrono::seconds>(mins);
        m_black->m_timer = Timer<std::chrono::seconds>(mins);
    }
}

auto Match::remainingTime(Color c) const
{
    return (c == Color::WHITE ? m_white : m_black)->m_timer.remainingTime();
}

Match::Winner Match::start()
{
    auto moves = m_white.get();
    auto notMoves = m_black.get();

    mainLoop(moves, notMoves);

    return moves->m_isInCheck ? (moves->m_player.color() == Color::BLACK ? Winner::black : Winner::white) : Winner::stalemate;
}

void Match::mainLoop(PlayerAttributes* moves, PlayerAttributes* notMoves)
{
    using namespace std::chrono_literals;

    std::future<Move> fut;
    Move m;

    moves->m_timer.start();
    notMoves->m_timer.start(); 
    notMoves->m_timer.suspend();

    while (!checkmate && !stalemate && !expired)
    {
        m_drawer->drawPlay(*this);

        moves->m_timer.resume();
        waitForInput(fut, moves->m_timer);
        if (expired) 
        {
            return;
        }
        if (!moves->m_player.isValidMove(fut.get()))
        {
            continue;
        }
        completeMove(moves, notMoves);

        moves->m_timer.suspend();
        std::swap(moves, notMoves);
    }
    m_drawer->drawPlay(*this);
}

void Match::waitForInput(std::future<Move>& f, auto& timer)
{
    using namespace std::chrono_literals;
    f = m_input->getMove();

    while (!m_input->isMoveRetrieved())
    {
        if (m_matchAlias.tm != Settings::Match::Time::no_time && timer.remainingTime() <= 0s)
        {
            expired = true;
            break;
        }
    }
}

void Match::completeMove(PlayerAttributes* moves, PlayerAttributes* notMoves)
{
    std::optional<const Piece*> kicked;

    moves->m_isInCheck = false;

    kicked = moves->m_player.move();
    if (kicked.has_value())
    {
        notMoves->m_player.removePiece(kicked.value());
    }

    auto checkingPieces = moves->m_player.piecesAccessingSquare(notMoves->m_player.kingCoord());
    if (!checkingPieces.empty())
    {
        notMoves->m_isInCheck = true;
        checkmate = !isEscapable(moves, notMoves);
        
        if (checkingPieces.size() == 1 && notMoves->m_player.isAccessibleSquare(checkingPieces[0]->coord()))
        {
            checkmate = false;
        }
    }
    else
    {
        stalemate = isStalemate(moves, notMoves);
    }
}

bool Match::isEscapable(PlayerAttributes* moves, PlayerAttributes* notMoves)
{
    auto escape = notMoves->m_player.kingsAccessibleSquares();
    for (auto sqr : escape)
    {
        if (!moves->m_player.isAccessibleSquare(sqr))
        {
            return true;
        }
    }
    return false;
}

bool Match::isStalemate(PlayerAttributes* moves, PlayerAttributes* notMoves)
{
    if (notMoves->m_player.isAbleToMove() || notMoves->m_player.isMovableKing())
    {
        auto piecesMovable = notMoves->m_player.piecesAbleToMove();
        
        for (const auto& p : piecesMovable)
        {
            m_board->setPiece(nullptr, p->coord());
            if (!moves->m_player.isAccessibleSquare(notMoves->m_player.kingCoord()))
            {
                m_board->setPiece(p, p->coord());
                return false;
            }
            m_board->setPiece(p, p->coord());
        }
        auto squaresForKing = notMoves->m_player.kingsAccessibleSquares();

        for (auto sqr : squaresForKing)
        {
            if (!moves->m_player.isAccessibleSquare(sqr))
            {
                return false;;
            }
        }
    }
    return true;
}
} // namespace Chess
