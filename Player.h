//
// Created by Sirzh on 15.04.2021.
//

#pragma once

#include <vector>
#include <array>
#include <memory>
#include "Primitives.h"
#include "Piece/Pieces.hpp"
#include "Board.h"

namespace Chess 
{
class Player 
{
public:
    Player(Board* b, Color c);

    std::pair<bool, const Piece*> tryMove(Coordinates from, Coordinates to);

    std::vector<Piece*> piecesAccessingSquare(Coordinates to) const;
    bool                isAccessedSquare(Coordinates to)      const;
    
    void setCheck(bool ch) { _inCheck = ch; }

    bool isAbleToMove() const;

    Coordinates kingCoord() const { return _king->coord(); }
    bool        isInCheck() const { return _inCheck; }
    Color       color()     const { return _color; }
    Board*      board()     const { return _board; }

private:
    static constexpr auto pawns = 8;
    static constexpr auto allPiecesExceptKing = 15;

    bool         _inCheck;
    Board*       _board;
    const Color  _color;

    template <std::size_t N>
    using Pieces = std::array<std::shared_ptr<Piece>, N>;

    Pieces<allPiecesExceptKing> _pieces;
    std::shared_ptr<Piece>      _king;

    std::shared_ptr<Piece> leftRook;
    std::shared_ptr<Piece> rightRook;

    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
};
}
