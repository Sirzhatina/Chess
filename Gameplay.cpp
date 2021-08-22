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

int Gameplay::start()
{
    Traits::Coordinates from, to;

    auto moves = &white;
    auto notMoves = &black;

    while (showGoesOn())
    {
        try 
        {
            inputToMove(from, to);
            if (from == to)
            {
                continue;
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