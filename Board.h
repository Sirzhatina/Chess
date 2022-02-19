//
// Created by Sirzh on 10.05.2021.
//

#pragma once

#include <array>
#include "Primitives.h"

namespace Chess 
{
class Player;
class Piece;

class Board 
{
public:
    struct Square { Coordinates coord; const Piece* piece{ nullptr }; };

    Board();
    ~Board() = default;

    void addPlayer(Player* pl);

    const Piece* setPiece(const Piece* p, Coordinates coord);
    const Piece* getPiece(Coordinates coord) const;

private:
    std::array<std::array<Square, boardSize>, boardSize> board;
    Player* players[2]{ nullptr, nullptr };

    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
};
} // ends namespace Chess
