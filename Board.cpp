//
// Created by Sirzh on 10.05.2021.
//

#include "Board.h"


Board::Board()
{
    int hor = 1;
    int vert = 8;
    bool color = false;

    for (auto& arr: board)
    {
        for (auto& sqr: arr)
        {
            sqr = new Square(Horizontal(hor++), Vertical(vert), Color(color));
            color = !color;
        }
        color = !color;
        hor = 1;
        vert--;
    }
}

Board::~Board()
{
    for (auto& arr: board)
    {
        for (auto& sqr: arr)
        {
            delete sqr;
        }
    }
}