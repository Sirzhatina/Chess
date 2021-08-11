#include "Gameplay.h"
#include <iostream>

int Gameplay::start()
{
    char xFrom, yFrom;
    char xTo, yTo;

    Traits::Coordinates from, to;

    while (showGoesOn())
    {
        std::cout << "Enter coordinates to move to and from: ";
        std::cin.get(xFrom).get(yFrom);
        std::cin.get(xTo).get(yTo);

        from = convertCoordinates(xFrom - 'a' - 1, yFrom - '0');
        to = convertCoordinates(xTo - 'a' - 1, yTo - '0');


    }
}