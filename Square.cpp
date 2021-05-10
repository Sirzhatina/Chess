//
// Created by Sirzh on 17.04.2021.
//

#include "Square.h"
#include <cctype>


bool Square::convertCoord(char horiz, char vert)
{
    horiz = tolower(horiz);

    if (horiz < 'a' || horiz > 'h' || vert < '1' || vert > '8')
    {
        return false;
    }
    this->x = static_cast<Horizontal>(horiz - 'a' + 1);
    this->y = static_cast<Vertical>(vert - '1' + 1);

    return true;
}