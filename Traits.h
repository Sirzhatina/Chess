//
// Created by Sirzh on 09.08.2021.
//

#ifndef CHESS_TRAITS_H
#define CHESS_TRAITS_H

class Piece;

namespace Traits
{

constexpr auto boardSize = 8;

enum class Horizontal {
    A, B, C, D, E, F, G, H
};
enum class Vertical {
    one, two, three, four, five, six, seven, eight
};

struct Coordinates {
    Horizontal x;
    Vertical y;
};

enum class Color {
    BLACK, WHITE
};
}

#endif //CHESS_TRAITS_H
