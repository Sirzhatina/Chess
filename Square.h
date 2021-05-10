//
// Created by Sirzh on 17.04.2021.
//

#ifndef CHESS_SQUARE_H
#define CHESS_SQUARE_H

#include <memory>

enum class Horizontal { NULLPOS, A, B, C, D, E, F, G, H };
enum class Vertical { NULLPOS, one, two, three, four, five, six, seven, eight };

class Piece;
class Square {
    Horizontal x = Horizontal::NULLPOS;
    Vertical y = Vertical::NULLPOS;
    std::shared_ptr<Piece> piece = nullptr;

public:
    Square() = default;
    Square(Horizontal X, Vertical Y, std::shared_ptr<Piece> p = nullptr): x(X), y(Y), piece(std::move(p)) { }

    bool convertCoord(char horiz, char vert);
};


#endif //CHESS_SQUARE_H
