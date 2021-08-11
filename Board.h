//
// Created by Sirzh on 10.05.2021.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <array>
#include "Traits.h"

class Player;
class Piece;
class Square;

class Board {
    static constexpr auto SIZE = 8;
    std::array<std::array<Square*, SIZE>, SIZE> board;

    Player* players[2]{ nullptr, nullptr };
public:
    Board();
    ~Board();

    void addPlayer(Player* pl);
    inline void setPiece(Piece* p, Traits::Coordinates coord);
    inline Square& getSquare(Traits::Coordinates coord);
};

#endif //CHESS_BOARD_H
