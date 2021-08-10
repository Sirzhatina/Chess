//
// Created by Sirzh on 10.05.2021.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <array>
#include "Traits.h"
#include "Square.h"

class Player;

class Board {
    static constexpr auto SIZE = 8;

    std::array<std::array<Square*, SIZE>, SIZE> board;
public:
    Board();
    ~Board();
    void setPieces(const Player& pl);
};

#endif //CHESS_BOARD_H
