#include "Gameplay.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include <vector>
#include <cstdlib>
#include <iostream>

namespace Chess
{

Gameplay::Gameplay(std::shared_ptr<const IBoardDrawer> drawer, std::shared_ptr<IInputHandler> input): _drawer(drawer), _input(input)
{
    _board = std::make_shared<Board>();
    _white = std::make_unique<Player>(_board.get(), Color::WHITE);
    _black = std::make_unique<Player>(_board.get(), Color::BLACK);
}

Gameplay::Winner Gameplay::start()
{
    auto moves = _white.get();
    auto notMoves = _black.get();

    mainLoop(moves, notMoves);

    return moves->isInCheck() ? (moves->color() == Color::BLACK ? Winner::black : Winner::white) : Winner::stalemate;
}

void Gameplay::mainLoop(Player* moves, Player* notMoves)
{
    Move m;
    std::optional<const Piece*> kicked;

    _drawer->drawBoard(_board);

    while (!checkmate && !stalemate)
    {
        try
        {
            m = _input->getMove();   
        }
        catch(const std::range_error& e)
        {
            std::cout << "Incorrect input: " << e.what() << '\n';
            continue;
        }
        
        if (!moves->isValidMove(m))
        {
            std::cout << "Not your square!" << std::endl;
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

        _drawer->drawBoard(_board);
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
            _board->setPiece(nullptr, p->coord());
            if (!moves->isAccessibleSquare(notMoves->kingCoord()))
            {
                _board->setPiece(p, p->coord());
                return false;
            }
            _board->setPiece(p, p->coord());
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
