//
// Created by Sirzh on 09.08.2021.
//

#ifndef CHESS_TRAITS_H
#define CHESS_TRAITS_H

namespace Chess
{

constexpr auto boardSize = 8;

enum class Horizontal {
    A, B, C, D, E, F, G, H, NPOS
};
enum class Vertical {
    one, two, three, four, five, six, seven, eight, NPOS
};

struct Coordinates {
    Horizontal x;
    Vertical y;
};
constexpr Coordinates NULLPOS{ Horizontal::NPOS, Vertical::NPOS };
inline bool operator==(const Coordinates& c1, const Coordinates& c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(const Coordinates& c1, const Coordinates& c2) { return !(c1 == c2); }

enum class Color {
    BLACK, WHITE
};
}

#endif //CHESS_TRAITS_H
