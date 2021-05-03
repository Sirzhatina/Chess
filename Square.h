//
// Created by Sirzh on 17.04.2021.
//

#ifndef CHESS_SQUARE_H
#define CHESS_SQUARE_H

enum class Horizontal { A = 1, B, C, D, E, F, G, H };
enum class Vertical { one = 1, two, three, four, five, six, seven, eight };

class Square {
    Horizontal x;
    Vertical y;

};


#endif //CHESS_SQUARE_H
