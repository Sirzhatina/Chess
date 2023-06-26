#include "Primitives.hpp"

namespace Chess
{

    Coordinates::Coordinates(Horizontal x_, Vertical y_) noexcept: x(x_), y(y_) { }

    Coordinates::Coordinates(int x_, int y_)
    { 
        auto coord = makeCoord(x_, y_);
        if (!coord.has_value()) 
            throw std::range_error("Coordinates are out of range");
        *this = *coord;
    }

    std::optional<Coordinates> Coordinates::makeCoord(int x_, int y_) noexcept
    {
        if (x_ < 0 || x_ >= boardSize || y_ < 0 || y_ >= boardSize)
            return {};
        return {{Horizontal{x_}, Vertical{y_}}};
    }

    bool Coordinates::tryShiftAt(int x_, int y_)
    {
        auto coord = makeCoord(int(x) + x_, int(y) + y_);
        if (!coord.has_value())
        {
            return false;
        }
        *this = *coord;
        return true;
    }
} // namespace Chess
