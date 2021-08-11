//
// Created by Sirzh on 10.05.2021.
//

#include <stdexcept>
#include "Board.h"
#include "Player.h"
#include "Square.h"


Board::Board()
{
    bool color = false;

    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            board[i][j] = new Square
                    {
                        Traits::Horizontal{ j },
                        Traits::Vertical{ (SIZE - 1) - i },
                        Traits::Color{ color }
                    };
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

void Board::addPlayer(Player *pl)
{
    if (players[0])
    {
        players[0] = pl;
    }
    else if (players[1])
    {
        players[1] = pl;
    }
    else
    {
        throw std::runtime_error{ "Players are already added!" };
    }
}

void Board::setPiece(Piece *p, Traits::Coordinates coord) { board[SIZE - int(coord.v) - 1][int(coord.h)]->setPiece(p); }

Square& Board::getSquare(Traits::Coordinates coord) { return *board[SIZE - int(coord.v)][int(coord.h)]; }