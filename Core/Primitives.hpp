//
// Created by Sirzh on 09.08.2021.
//
#pragma once

#include <utility>

namespace Chess
{
constexpr auto boardSize = 8;

enum class Horizontal { A,   B,   C,     D,    E,    F,   G,     H     };
enum class Vertical   { one, two, three, four, five, six, seven, eight };

struct Coordinates
{
    Horizontal x;
    Vertical y;
};
inline bool operator==(const Coordinates& c1, const Coordinates& c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(const Coordinates& c1, const Coordinates& c2) { return !(c1 == c2); }

struct Move
{
    Coordinates from;
    Coordinates to;
    bool operator==(const Move& m) const { return from == m.from && to == m.to; }
    bool operator!=(const Move& m) const { return !(*this == m); }
};

enum class Color { BLACK, WHITE };
}
