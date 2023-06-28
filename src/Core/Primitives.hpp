//
// Created by Sirzh on 09.08.2021.
//
#pragma once

#include <optional>

namespace Chess
{
constexpr auto boardSize = 8;

enum class Horizontal { A,   B,   C,     D,    E,    F,   G,     H     };
enum class Vertical   { one, two, three, four, five, six, seven, eight };

enum class Color : bool { BLACK, WHITE };

/// @brief Integer-based pair of values to inform about piece's location
struct Coordinates
{
    Horizontal x;
    Vertical   y;

    Coordinates() = default;
    
    /// @brief Creates coordinates converting pair of integer values
    /// @param x_ Value on a horizontal axis
    /// @param y_ Value on a vertical axis
    /// @exception  std::range_error if arguments are out of default boardSize (8) value
    Coordinates(int x_, int y_);

    /// @brief Constructs the object trivially from already existed set of values
    Coordinates(Horizontal x_, Vertical y_) noexcept;

    /// @brief Tries to create wrapped coordinates, with no exception thrown
    /// @param x_ Value on a horizontal axis
    /// @param y_ Value on a vertical axis
    /// @return Optional value with or without contained coordinates
    static std::optional<Coordinates> makeCoord(int x_, int y_) noexcept;

    /// @brief Tries to change current Coordinates shifting them on a given set of values 
    ///        and reports about result in a returned value
    /// @param x_ Value on a horizontal axis
    /// @param y_ Value on a vertical axis
    /// @return True if shifting hasn't led to out-of-range value, false otherwise
    bool tryShiftAt(int x_, int y_);

    auto operator<=>(const Coordinates& rhs) const = default;
};


struct Move
{
    Coordinates from;
    Coordinates to;

    auto operator<=>(const Move& rhs) const = default;
};

}
