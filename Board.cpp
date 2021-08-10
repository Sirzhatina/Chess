//
// Created by Sirzh on 10.05.2021.
//

#include "Board.h"


Board::Board()
{
    bool color = false;

    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            board[i][j] = new Square(Horizontal(j), Vertical((SIZE - 1) - i), Color(color));
            color = !color;
        }
        color = !color;
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