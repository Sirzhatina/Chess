//
// Created by Sirzh on 09.08.2021.
//
#pragma once

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

    Move() = default;
    Move(const std::pair<Coordinates, Coordinates>& p) : from(p.first), to(p.second) { }
};

enum class Color { BLACK, WHITE };
}
