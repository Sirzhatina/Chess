//
// Created by Sirzh on 17.04.2021.
//

#ifndef CHESS_SQUARE_H
#define CHESS_SQUARE_H

#include "Traits.h"

class Piece;
class Square
{
    const Traits::Coordinates coord;
    const Traits::Color color;
    Piece* piece;
public:
    Square(Traits::Horizontal X, Traits::Vertical Y, Traits::Color c, Piece* p = nullptr)
    : coord{ X, Y }
    , color{ c }
    , piece{ p }
    { }

    void setPiece(Piece* p) { piece = p; }
    void removePiece() { piece = nullptr; }
};


#endif //CHESS_SQUARE_H
