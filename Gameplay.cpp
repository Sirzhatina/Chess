#include "Gameplay.h"
#include <iostream>
#include <cstdlib>



void Gameplay::inputToMove(Traits::Coordinates& from, Traits::Coordinates& to) const
{
    char xFrom, yFrom;
    char xTo, yTo;

    std::cout << "Enter coordinates to move from and to (e.g. e2 e4): ";
    std::cin.get(xFrom).get(yFrom);
    std::cin.get();                   // eats ' '
    std::cin.get(xTo).get(yTo).get(); // eats '\n' in the end

    if (xFrom < 'a' || xFrom > 'h' || xTo < 'a' || xTo > 'h' ||
        yFrom < '1' || yFrom > '8' || yTo < '1' || yTo > '8')
    {
        throw std::runtime_error{ "Invalid input!" };
    }
    
    from = convertCoordinates(xFrom - 'a', yFrom - '1');
    to = convertCoordinates(xTo - 'a', yTo - '1');
}

bool Gameplay::possibleMove(Player* moves, Player* checks, Traits::Coordinates from, Traits::Coordinates to) const
{
    Piece* defeated{ nullptr };
    Piece* piece = const_cast<Piece*>(board->getPiece(from));

    if (piece->possibleMove(to) && piece->getPlayer() == moves)
    {
        defeated = board->setPiece(piece, to);
    }
    else
    {
        return false;
    }
    bool result = (from == moves->getKingCoord()) ? checks->accessToSquare(to) : checks->accessToSquare(moves->getKingCoord());

    board->setPiece(board->setPiece(defeated, to), from); // swaps defeated and piece pieces on the board
    return result;
}

int Gameplay::start()
{
    Traits::Coordinates from, to;

    auto moves = &white;
    auto notMoves = &black;

    Piece* defeated{ nullptr };

    while (showGoesOn())
    {
        try 
        {
            inputToMove(from, to);
            if (from == to)
            {
                continue;
            }
            if (!possibleMove(moves, notMoves, from, to))
            {
                throw std::runtime_error{ "Impossible move" };
            }
            moves->move(from, to);
            std::swap(moves, notMoves);
        }
        catch (const std::runtime_error& err)
        {
            std::cout << err.what() << std::endl;
            continue;
        }

        whiteMove = !whiteMove;
    }
}