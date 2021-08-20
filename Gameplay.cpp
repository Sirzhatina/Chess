#include "Gameplay.h"
#include <iostream>
#include <cstdlib>




int Gameplay::start()
{
    char xFrom, yFrom;
    char xTo, yTo;

    Traits::Coordinates from, to;

    auto moves = &white;
    auto notMoves = &black;

    while (showGoesOn())
    {
        std::cout << "Enter coordinates to move from and to (e.g. e2 e4): ";
        std::cin.get(xFrom).get(yFrom);
        std::cin.get(); // eats ' '
        std::cin.get(xTo).get(yTo);

        from = convertCoordinates(xFrom - 'a', yFrom - '1');
        to = convertCoordinates(xTo - 'a', yTo - '1');

        try 
        {
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