//
// Created by Sirzh on 09.08.2021.
//
#pragma once

#include <utility>
#include <stdexcept>
#include <optional>

namespace Chess
{
constexpr auto boardSize = 8;

enum class Horizontal { A,   B,   C,     D,    E,    F,   G,     H     };
enum class Vertical   { one, two, three, four, five, six, seven, eight };

struct Coordinates
{
    Horizontal x;
    Vertical   y;

    Coordinates() = default;
    Coordinates(Horizontal x_, Vertical y_): x(x_), y(y_) { }

    static std::optional<Coordinates> makeCoord(int x_, int y_) noexcept
    {
        if (x_ < 0 || x_ >= boardSize || y_ < 0 || y_ >= boardSize)
            return {};
        return {{Horizontal{x_}, Vertical{y_}}};
    }

    Coordinates(int x_, int y_)
    { 
        if (x_ < 0 || x_ >= boardSize || y_ < 0 || y_ >= boardSize) 
            throw std::range_error("Coordinates are out of range");
        x = Horizontal(x_);
        y = Vertical(y_);
    }

    bool tryShift(int x_, int y_)
    {
        auto isOut = [&](int first, int sec) { return first + sec < 0 || first + sec >= boardSize; };
        if (isOut(int(x), x_) || isOut(int(y), y_))
        {
            return false;
        }
        x = Horizontal{int(x) + x_};
        y = Vertical{int(y) + y_};

        return true;
    }

    bool operator==(const Coordinates& c) const { return x == c.x && y == c.y; }
    bool operator!=(const Coordinates& c) const { return !(*this == c); }
};


struct Move
{
    Coordinates from;
    Coordinates to;

    bool operator==(const Move& m) const { return from == m.from && to == m.to; }
    bool operator!=(const Move& m) const { return !(*this == m); }
};

enum class Color : bool { BLACK, WHITE };
}
