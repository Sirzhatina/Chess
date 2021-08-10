//
// Created by Sirzh on 17.04.2021.
//

#ifndef CHESS_SQUARE_H
#define CHESS_SQUARE_H

#include "Traits.h"

class Piece;
class Square
{
    Coordinates coord;
    Color color;
    Piece* piece;
public:
    Square(Horizontal X, Vertical Y, Color c, Piece* p = nullptr)
    :
    coord{ X, Y }
    , color{ c }
    , piece{ p } { }

    void setPiece(Piece* p) { piece = p; }
};


#endif //CHESS_SQUARE_H
