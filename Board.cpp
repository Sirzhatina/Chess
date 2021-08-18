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
            board[i][j] = new Square
                    {
                        Traits::Coordinates { Traits::Horizontal{ j }, Traits::Vertical{ (Traits::boardSize - 1) - i } }
                    };
        }
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

void Board::setPiece(Piece *p, Traits::Coordinates coord)
{
    if (p->getPlayer() == players[0] || p->getPlayer() == players[1])
    {
        getSquare(coord)->piece = p;
    }  
}