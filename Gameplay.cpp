#include "Gameplay.h"
#include "Logger.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <regex>

namespace Chess
{

Gameplay::Gameplay(inputHandler getMove) : _getMove(getMove)
{
    _board = std::make_unique<Board>();
    _white = std::make_unique<Player>(_board.get(), Color::WHITE);
    _black = std::make_unique<Player>(_board.get(), Color::BLACK);
}

Color Gameplay::start()
{
    auto moves = _white.get();
    auto notMoves = _black.get();

    Move m;
    std::optional<const Piece*> kicked;

    while (!checkmate && !stalemate)
    {
        m = _getMove();
        if (!moves->isValidMove(m))
        {
            continue;
        }

        kicked = moves->move();
        if (kicked.has_value())
        {
            notMoves->removePiece(kicked.value());
        }

        auto checkingPieces = moves->piecesAccessingSquare(notMoves->kingCoord());
        if (!checkingPieces.empty())
        {
            notMoves->setCheck(true);
            checkmate = true;

            auto escape = notMoves->kingAccessedSquares();
            for (auto sqr : escape)
            {
                if (!moves->isAccessedSquare(sqr))
                {
                    checkmate = false;
                    break;
                }
            }

            if (checkingPieces.size() == 1 && notMoves->isAccessedSquare(checkingPieces[0]->coord()))
            {
                checkmate = false;
            }
        }
        else
        {
            stalemate = true;

            if (notMoves->isAbleToMove() || notMoves->isMovableKing())
            {
                auto piecesMovable = notMoves->piecesAbleToMove();
                
                for (const auto& p : piecesMovable)
                {
                    _board->setPiece(nullptr, p->coord());
                    if (!moves->isAccessedSquare(notMoves->kingCoord()))
                    {
                        stalemate = false;
                    }
                    _board->setPiece(p, p->coord());
                }

                auto squaresForKing = notMoves->kingAccessedSquares();

                for (auto sqr : squaresForKing)
                {
                    if (!moves->isAccessedSquare(sqr))
                    {
                        stalemate = false;
                    }
                }
            }
        }
        std::swap(moves, notMoves);
    }

}
} // namespace Chess
