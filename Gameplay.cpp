#include "Gameplay.h"
#include "Logger.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <regex>

namespace Chess
{
void Gameplay::inputToMove(Coordinates& from, Coordinates& to) const
{
    std::string coord;
    std::regex pattern(R"([a-h][1-8] [a-h][1-8])");

    std::cout << (whiteMove ? "White" : "Black") << " moves: ";
    std::getline(std::cin, coord);
    Logger::getLogger(defaultLogFile).write(coord);
    if (coord == Gameplay::quitCommand)
    {
        throw ExitExcep{ "Bye\n" };
    }
    else if (!std::regex_match(coord, pattern))
    {
        throw std::runtime_error{ "Invalid input!" };
    }    
    from = convertCoordinates(coord[0] - 'a', coord[1] - '1');
    to = convertCoordinates(coord[3] - 'a', coord[4] - '1');
}

bool Gameplay::possibleMove(Player* moves, Player* checks, Coordinates from, Coordinates to) const
{
    if (!board->getPiece(from))
    {
        return false;
    }
    Piece* defeated{ nullptr };
    Piece* piece = const_cast<Piece*>(board->getPiece(from));

    if (piece->possibleMove(to) && piece->getPlayer() == moves)
    {
        defeated = board->setPiece(board->setPiece(nullptr, from), to);
    }
    else if (piece->getCoord() == moves->getKingCoord() && piece->isFirstMove() && std::abs(int(to.x) - int(from.x)) == 2) // is castling
    {
        Coordinates mid{ Horizontal(int(from.x) + (int(to.x) > int(from.x)) ? 1 : -1), from.y };

        return !checks->isAccessedSquare(mid) && !checks->isAccessedSquare(to) && !checks->isAccessedSquare(from);
    }
    else
    {
        return false;
    }

    if (defeated)
    {
        defeated->setCoordinates(NULLPOS);
    }
    bool result = (from == moves->getKingCoord()) ? !checks->isAccessedSquare(to) : !checks->isAccessedSquare(moves->getKingCoord());

    board->setPiece(board->setPiece(defeated, to), from); // swaps back defeated and piece variables on the board
    if (defeated)
    {
        defeated->setCoordinates(to);
    }
    return result;
}

bool Gameplay::isCheckmate(Player* checks, Player* inCheck) const
{
    std::vector<Piece*> checkPieces = checks->piecesAccessingSquare(inCheck->getKingCoord());  // containts 0, 1 or 2 pieces
    if (checkPieces.empty())
    {
        inCheck->setCheck(false);
        return false;
    }
    else
    {
        inCheck->setCheck(true);
    }
    std::vector<Coordinates> availableForKing = allSquaresForKing(inCheck, checks);

    if (checkPieces.size() > 1)
    {
        return availableForKing.empty();
    }
    std::vector<Coordinates> allCheckSquares = checkPieces[0]->squaresBefore(inCheck->getKingCoord());

    const Piece* king = board->getPiece(inCheck->getKingCoord());
    for (const auto sqr : allCheckSquares)
    {
        // bug #2 is hidden here
        if (inCheck->isAccessedSquare(sqr))
        {
            return false;
        }
    }
    return availableForKing.empty();
}

std::vector<Coordinates> Gameplay::allSquaresForKing(const Player* moves, const Player* notMoves) const
{
    std::vector<Coordinates> result;

    const Piece* pieceOnSquare{ nullptr };
    Coordinates currentSquare;

    for (int x = int(moves->getKingCoord().x) - 1, lim = x + 3; x < lim; x++)
    {   
        for (int y = int(moves->getKingCoord().y) - 1, lim = y + 3; y < lim; y++)
        {
            if (x > 0 && x < boardSize && y > 0 && y < boardSize)
            {
                currentSquare.x = Horizontal{x};
                currentSquare.y = Vertical{y};
                pieceOnSquare = board->getPiece(currentSquare);

                if ((!pieceOnSquare || pieceOnSquare && pieceOnSquare->getColor() != moves->getColor()) &&
                    moves->getKingCoord() != currentSquare &&
                    !notMoves->isAccessedSquare(currentSquare))
                {
                    result.push_back(currentSquare);
                }
            }
        }
    }
    return result;
}

bool Gameplay::kingCanMove(const Player* moves, const Player* notMoves) const
{
    const Piece* pieceOnSquare{ nullptr };
    Coordinates currentSquare;

    for (int x = int(moves->getKingCoord().x) - 1, lim = x + 3; x < lim; x++)
    {   
        for (int y = int(moves->getKingCoord().y) - 1, lim = y + 3; y < lim; y++)
        {
            if (x > 0 && x < boardSize && y > 0 && y < boardSize)
            {
                currentSquare.x = Horizontal{x};
                currentSquare.y = Vertical{y};
                pieceOnSquare = board->getPiece(currentSquare);

                if ((!pieceOnSquare || pieceOnSquare && pieceOnSquare->getColor() != moves->getColor()) &&
                    moves->getKingCoord() != currentSquare &&
                    !notMoves->isAccessedSquare(currentSquare))
                {
                    return true;
                }
            }
        }
    }
    return false;   
}

int Gameplay::start()
{
    Coordinates from, to;
    while (showGoesOn() && !stalemate)
    {
        try
        {
            inputToMove(from, to);
            if (from == to)
            {
                continue;
            }
            movingProccess(from, to);
        }
        catch (const std::runtime_error& err)
        {
            std::cout << err.what() << std::endl;
            Logger::getLogger().write(err.what());
            continue;
        }
        catch (const ExitExcep& err)
        {
            std::cout << err.what() << std::endl;
            Logger::getLogger().write(err.what());
            return EXIT_SUCCESS;
        }
        catch (...)
        {
            Logger::getLogger().write("Something went wrong.");
            return EXIT_FAILURE;
        }
    }
    endgame();
    return EXIT_SUCCESS;
}

void Gameplay::movingProccess(Coordinates from, Coordinates to)
{
    auto moves = whiteMove ? &white : &black;
    auto notMoves = whiteMove ? &black : &white;

    Piece* defeated{ nullptr };

    if (!possibleMove(moves, notMoves, from, to))
    {
        throw std::runtime_error{ "Impossible move" };
    }
    defeated = moves->move(from, to);   // returns defeated piece or nullptr if to-square is empty
    Notify();
    if (defeated)
    { 
        defeated->setCoordinates(NULLPOS);
    }
    if (isCheckmate(moves, notMoves))
    {
        notMoves->setCheckmate(true);
        return;
    }
    stalemate = !kingCanMove(moves, notMoves) && !moves->isAbleToMove();
    if (stalemate)
    {
        return;
    }
    whiteMove = !whiteMove;
}

void Gameplay::endgame() const 
{
    if (!showGoesOn())
    {
        std::cout << winMessage();
        Logger::getLogger().write(winMessage());
    }
    else
    {
        std::cout << drawMessage;
        Logger::getLogger().write(winMessage());
    }
    system("pause");
}

void Gameplay::Notify() const
{
    for (auto ob : observers)
    {
        ob->handleEvent(this);
    }
}
} // ends namespace Chess