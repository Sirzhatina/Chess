#include "Gameplay.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include <vector>
#include <cstdlib>
#include <iostream>

namespace Chess
{

Gameplay::Gameplay(std::shared_ptr<const IDrawer> drawer, std::shared_ptr<IInputHandler> input): m_drawer(drawer), m_input(input)
{
    m_board = std::make_shared<Board>();
    m_white.m_player = std::make_unique<Player>(m_board.get(), Color::WHITE);
    m_black.m_player = std::make_unique<Player>(m_board.get(), Color::BLACK);

    if (Settings::instance().m_mSettings.tm != Settings::Match::Time::no_time)
    {
        auto mins = std::chrono::minutes(int(Settings::instance().m_mSettings.tm));

        m_white.m_remainingTime = Timer<std::chrono::seconds>::makeTimer(mins);
        m_black.m_remainingTime = Timer<std::chrono::seconds>::makeTimer(mins);
    }
}

auto Gameplay::remainingTime(Color c) const
{
    return (c == Color::WHITE ? m_white : m_black).m_remainingTime->remainingTime();
}

Gameplay::Winner Gameplay::start()
{
    auto moves = m_white.m_player.get();
    auto notMoves = m_black.m_player.get();

    mainLoop(moves, notMoves);

    return moves->isInCheck() ? (moves->color() == Color::BLACK ? Winner::black : Winner::white) : Winner::stalemate;
}

void Gameplay::mainLoop(Player* moves, Player* notMoves)
{
    std::optional<Move> m;
    std::optional<const Piece*> kicked;

    m_drawer->drawBoard(m_board);

    while (!checkmate && !stalemate)
    {
        m = m_input->getMove();
        
        if (!m || !moves->isValidMove(*m))
        {
            continue;
        }
        moves->setCheck(false);

        kicked = moves->move();
        if (kicked.has_value())
        {
            notMoves->removePiece(kicked.value());
        }

        auto checkingPieces = moves->piecesAccessingSquare(notMoves->kingCoord());
        if (!checkingPieces.empty())
        {
            notMoves->setCheck(true);
            checkmate = !isEscapable(moves, notMoves);
            
            if (checkingPieces.size() == 1 && notMoves->isAccessibleSquare(checkingPieces[0]->coord()))
            {
                checkmate = false;
            }
        }
        else
        {
            stalemate = isStalemate(moves, notMoves);
        }
        std::swap(moves, notMoves);

        m_drawer->drawBoard(*m_board);
    }
}

bool Gameplay::isEscapable(Player* moves, Player* notMoves)
{
    auto escape = notMoves->kingsAccessibleSquares();
    for (auto sqr : escape)
    {
        if (!moves->isAccessibleSquare(sqr))
        {
            return true;
        }
    }
    return false;
}

bool Gameplay::isStalemate(Player* moves, Player* notMoves)
{
    if (notMoves->isAbleToMove() || notMoves->isMovableKing())
    {
        auto piecesMovable = notMoves->piecesAbleToMove();
        
        for (const auto& p : piecesMovable)
        {
            m_board->setPiece(nullptr, p->coord());
            if (!moves->isAccessibleSquare(notMoves->kingCoord()))
            {
                m_board->setPiece(p, p->coord());
                return false;
            }
            m_board->setPiece(p, p->coord());
        }
        auto squaresForKing = notMoves->kingsAccessibleSquares();

        for (auto sqr : squaresForKing)
        {
            if (!moves->isAccessibleSquare(sqr))
            {
                return false;;
            }
        }
    }
    return true;
}
} // namespace Chess
