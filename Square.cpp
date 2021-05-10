//
// Created by Sirzh on 17.04.2021.
//

#include "Square.h"
#include <cctype>


bool Square::convertCoord(char x, char y, Square& returned) {
    Horizontal tempX;
    Vertical tempY;

    x = tolower(x);

    if (x < 'a' || x > 'h' || y < '1' || y > '8')
    {
        return false;
    }

    returned.x = static_cast<Horizontal>(x - 'a');
    returned.y = static_cast<Vertical>(y - '0');

    return true;
}