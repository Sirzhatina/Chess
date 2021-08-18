//
// Created by Sirzh on 10.05.2021.
//

#include <stdexcept>
#include "Board.h"
#include "Player.h"
#include "Piece/Piece.h"


Board::Board()
{
    using x = Traits::Horizontal;
    using y = Traits::Vertical;
    using s = Square;
    using a = std::array<s, Traits::boardSize>;
    
    board = new std::array<a, Traits::boardSize>
    {
        a{ s{{ x::A, y{7} }}, s{{ x::B, y{7} }}, s{{ x::C, y{7} }}, s{{ x::D, y{7} }}, s{{ x::E, y{7} }}, s{{ x::F, y{7} }}, s{{ x::G, y{7} }}, s{{ x::H, y{7} }} },
        a{ s{{ x::A, y{6} }}, s{{ x::B, y{6} }}, s{{ x::C, y{6} }}, s{{ x::D, y{6} }}, s{{ x::E, y{6} }}, s{{ x::F, y{6} }}, s{{ x::G, y{6} }}, s{{ x::H, y{6} }} },
        a{ s{{ x::A, y{5} }}, s{{ x::B, y{5} }}, s{{ x::C, y{5} }}, s{{ x::D, y{5} }}, s{{ x::E, y{5} }}, s{{ x::F, y{5} }}, s{{ x::G, y{5} }}, s{{ x::H, y{5} }} },
        a{ s{{ x::A, y{4} }}, s{{ x::B, y{4} }}, s{{ x::C, y{4} }}, s{{ x::D, y{4} }}, s{{ x::E, y{4} }}, s{{ x::F, y{4} }}, s{{ x::G, y{4} }}, s{{ x::H, y{4} }} },
        a{ s{{ x::A, y{3} }}, s{{ x::B, y{3} }}, s{{ x::C, y{3} }}, s{{ x::D, y{3} }}, s{{ x::E, y{3} }}, s{{ x::F, y{3} }}, s{{ x::G, y{3} }}, s{{ x::H, y{3} }} },
        a{ s{{ x::A, y{2} }}, s{{ x::B, y{2} }}, s{{ x::C, y{2} }}, s{{ x::D, y{2} }}, s{{ x::E, y{2} }}, s{{ x::F, y{2} }}, s{{ x::G, y{2} }}, s{{ x::H, y{2} }} },
        a{ s{{ x::A, y{1} }}, s{{ x::B, y{1} }}, s{{ x::C, y{1} }}, s{{ x::D, y{1} }}, s{{ x::E, y{1} }}, s{{ x::F, y{1} }}, s{{ x::G, y{1} }}, s{{ x::H, y{1} }} },
        a{ s{{ x::A, y{0} }}, s{{ x::B, y{0} }}, s{{ x::C, y{0} }}, s{{ x::D, y{0} }}, s{{ x::E, y{0} }}, s{{ x::F, y{0} }}, s{{ x::G, y{0} }}, s{{ x::H, y{0} }} }
    };
}

Board::~Board()
{
    delete board;
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
        (*board)[Traits::boardSize - int(coord.y) - 1][int(coord.x)].piece = p;
    }  
}