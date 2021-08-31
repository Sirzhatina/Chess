#include "Gameplay.h"
#include <iostream>
#include <vector>
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
    bool result = (from == moves->getKingCoord()) ? checks->isAccessedSquare(to) : checks->isAccessedSquare(moves->getKingCoord());

    board->setPiece(board->setPiece(defeated, to), from); // swaps defeated and piece variables on the board
    return result;
}

bool Gameplay::isCheckmate(Player* checks, Player* inCheck)
{
    std::vector<Piece*> checkPieces = checks->piecesAccessingSquare(inCheck->getKingCoord());  // containts 0, 1 or 2 pieces
    if (checkPieces.empty())
    {
        return false;
    }
    else
    {
        inCheck->setCheck(true);
    }
    std::vector<Traits::Coordinates> squaresForKing;

    {
        const Piece* pieceOnSquare{ nullptr };
        Traits::Coordinates currentSquare;

        for (int x = int(inCheck->getKingCoord().x) - 1; x < 3; x++)
        {   
            for (int y = int(inCheck->getKingCoord().y) - 1; y < 3; y++)
            {
                currentSquare = { Traits::Horizontal{x}, Traits::Vertical{y} };
                pieceOnSquare = board->getPiece(currentSquare);

                if (x > 0 && x < Traits::boardSize && y > 0 && y < Traits::boardSize &&
                    inCheck->getKingCoord() != currentSquare)
                {
                    if (pieceOnSquare && pieceOnSquare->getColor() != inCheck->getColor() &&
                        !checks->isAccessedSquare(currentSquare))
                    {
                        squaresForKing.push_back(currentSquare);
                    }
                }
            }
        }
    }
    if (checkPieces.size() > 1 && squaresForKing.empty())
    {
        return true;
    }

    std::vector<Traits::Coordinates> allCheckSquares = checkPieces[0]->squaresBefore(inCheck->getKingCoord());

    const Piece* king = board->getPiece(inCheck->getKingCoord());
    for (const auto sqr : allCheckSquares)
    {
        if (inCheck->isAccessedSquare(sqr) && !king->possibleMove(sqr))
        {
            return false;
        }
    }
    return true;
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
            if (isCheckmate(moves, notMoves))
            {
                notMoves->setCheckmate(true);
            }
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