#include "Gameplay.h"
#include <iostream>

int Gameplay::start()
{
    char xFrom, yFrom;
    char xTo, yTo;

    Traits::Coordinates from, to;

    auto moves = &white;
    auto notMoves = &black;

    while (showGoesOn())
    {
        std::cout << "Enter coordinates to move from and to: ";
        std::cin.get(xFrom).get(yFrom);
        std::cin.get(xTo).get(yTo);

        from = convertCoordinates(xFrom - 'a', yFrom - '1');
        to = convertCoordinates(xTo - 'a', yTo - '1');

        if (isPossibleMove(from, to))
        {
            moves->move(from, to);

            
        }

        whiteMove = !whiteMove;
    }
}