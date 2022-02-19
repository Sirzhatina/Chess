//
// Created by Sirzh on 15.04.2021.
//

#pragma once

#include "..\Primitives.h"
#include <string>
#include <vector>

namespace Chess
{
class Board;
class Player;

class Piece
{
    const Player* _player;
    Coordinates   _currentCoord;
    bool          _firstMove{ true };

protected:
    bool isFriendlySquare(Coordinates square) const;
    bool isSameSquare(Coordinates square)     const { return coord() == square; }

public:
    Piece(const Player* p, Coordinates coord);
    virtual ~Piece() = default;

    virtual bool                     isPossibleMove(Coordinates to) const = 0;
    virtual std::vector<Coordinates> squaresBefore(Coordinates to)  const = 0;
    
    void setCoordinates(Coordinates to);

    const Player* player()      const { return _player; }
    Coordinates   coord()       const { return _currentCoord; }
    bool          isFirstMove() const { return _firstMove; }
};
}
