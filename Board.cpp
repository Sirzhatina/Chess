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
    auto player = (pl->color() == Color::WHITE ? _white : _black);
    if (player)
    {
        throw std::runtime_error{ "Player with such color is already added!" };
    }
    player = pl;
}

const Player* Board::enemyOf(const Player* pl) const
{
    if (pl == _white)
    {
        return _black;
    }
    if (pl == _black)
    {
        return _white;
    }
    throw std::runtime_error{ "Player doesn't play on this board" };
}

const Piece* Board::setPiece(const Piece *p, Coordinates coord)
{
    const Piece* previous = board[boardSize - int(coord.y) - 1][int(coord.x)].piece;
    board[boardSize - int(coord.y) - 1][int(coord.x)].piece = p;

    return previous;
}

const Piece* Board::getPiece(Coordinates coord) const { return board[boardSize - int(coord.y) - 1][int(coord.x)].piece; }

} // namespace Chess
