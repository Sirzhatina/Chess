//
// Created by Sirzh on 17.04.2021.
//

#ifndef CHESS_SQUARE_H
#define CHESS_SQUARE_H

#include <memory>

enum class Horizontal { A, B, C, D, E, F, G, H };
enum class Vertical { one, two, three, four, five, six, seven, eight };

class Piece;
class Square {
    Horizontal x;
    Vertical y;
    std::shared_ptr<Piece> piece;
public:
    Square(Horizontal X, Vertical Y, std::shared_ptr<Piece> p = nullptr): x(X), y(Y), piece(std::move(p)) { }

};


#endif //CHESS_SQUARE_H
