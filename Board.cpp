//
// Created by Sirzh on 10.05.2021.
//

#include <stdexcept>
#include "Board.h"
#include "Player.h"
#include "Piece/Pieces.hpp"

namespace Chess
{
Board::Board()
{    
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            board[i][j].coord.x = Horizontal{ j };
            board[i][j].coord.y = Vertical{ boardSize - i - 1 };
        }
    }
}

void Board::addPlayer(Player *pl)
{
    if (!players[0])
    {
        players[0] = pl;
    }
    else if (!players[1])
    {
        if (players[0]->color() == pl->color())
        {
            throw std::runtime_error{ "Players have the same color" };
        }
        players[1] = pl;
    }
    else
    {
        throw std::runtime_error{ "Players are already added!" };
    }
}

const Piece* Board::setPiece(const Piece *p, Coordinates coord)
{
    const Piece* previous = board[boardSize - int(coord.y) - 1][int(coord.x)].piece;
    board[boardSize - int(coord.y) - 1][int(coord.x)].piece = p;

    return previous;
}

const Piece* Board::getPiece(Coordinates coord) const { return board[boardSize - int(coord.y) - 1][int(coord.x)].piece; }

} // namespace Chess
