//
// Created by Sirzh on 17.04.2021.
//

#ifndef CHESS_SQUARE_H
#define CHESS_SQUARE_H

#include <memory>
#include "Piece/Piece.h"

enum class Horizontal { A, B, C, D, E, F, G, H };
enum class Vertical { one, two, three, four, five, six, seven, eight };

class Square {
    Horizontal x;
    Vertical y;

    std::unique_ptr<Piece> piece;

};


#endif //CHESS_SQUARE_H
