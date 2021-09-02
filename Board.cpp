//
// Created by Sirzh on 10.05.2021.
//

#include <stdexcept>
#include "Board.h"
#include "Player.h"
#include "Piece/Piece.h"


Board::Board()
{    
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            board[i][j].coord.x = Traits::Horizontal{ j };
            board[i][j].coord.y = Traits::Vertical{ Traits::boardSize - i - 1 };
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
        if (players[0]->getColor() == pl->getColor())
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

Piece* Board::setPiece(Piece *p, Traits::Coordinates coord)
{
    Piece* previous = board[Traits::boardSize - int(coord.y) - 1][int(coord.x)].piece;
    
    board[Traits::boardSize - int(coord.y) - 1][int(coord.x)].piece = p;
    board[Traits::boardSize - int(p->getCoord().y) - 1][int(p->getCoord().x)].piece = nullptr;

    return previous;
}