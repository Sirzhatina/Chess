//
// Created by Sirzh on 15.04.2021.
//

#pragma once

#include "..\Primitives.hpp"
#include <vector>

namespace Chess
{
class Player;

class Piece
{
    const Player* _player;
    Coordinates   _currentCoord;
    bool          _firstMove{ true };

protected:
    bool isFriendlySquare(Coordinates square) const;
    bool isSameSquare(Coordinates square)     const { return coord() == square; }

    virtual bool isValidRoute(Coordinates to) const = 0;
    virtual bool isClearRoute(Coordinates to) const = 0;
public:
    Piece(const Player* p, Coordinates coord);
    virtual ~Piece() = default;

    bool                     isPossibleMove(Coordinates to) const;
    virtual bool                     isAbleToMove()                 const = 0;
    virtual std::vector<Coordinates> squaresBefore(Coordinates to)  const = 0;
    
    void setCoordinates(Coordinates to);

    const Player* player()      const { return _player; }
    Coordinates   coord()       const { return _currentCoord; }
    bool          isFirstMove() const { return _firstMove; }
    // utility method for isAbleToMove()
    bool isAbleToSqr(Coordinates to, int x, int y) const { return to.tryShift(x, y) && isPossibleMove(to); }
};
}
