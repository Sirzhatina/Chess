export module Primitives;

import std.core;

export namespace Core
{
constexpr auto boardSize = 8;

enum class Horizontal { A,   B,   C,     D,    E,    F,   G,     H     };
enum class Vertical   { one, two, three, four, five, six, seven, eight };

struct Coordinates
{
    Horizontal x;
    Vertical   y;

    Coordinates() = default;
    Coordinates(Horizontal x_, Vertical y_);

    static std::optional<Coordinates> makeCoord(int x_, int y_) noexcept;

    Coordinates(int x_, int y_);

    bool tryShift(int x_, int y_);

    bool operator==(const Coordinates& c) const;
    bool operator!=(const Coordinates& c) const;
};


struct Move
{
    Coordinates from;
    Coordinates to;

    bool operator==(const Move& m) const;
    bool operator!=(const Move& m) const;
};

enum class Color : bool { BLACK, WHITE };
} // namespace Core
