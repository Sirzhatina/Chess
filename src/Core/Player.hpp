//
// Created by Sirzh on 15.04.2021.
//

#pragma once

#include <vector>
#include <array>
#include <memory>
#include <optional>
#include "Primitives.hpp"
#include "Piece/Pieces.hpp"
#include "Board.hpp"

namespace Chess 
{
class Player 
{
public:
    Player(Board* b, Color c);

    bool isValidMove(Move m) const;
    std::optional<const Piece*> move();

    bool isAccessibleSquare(Coordinates to) const;
    bool isAbleToMove()                     const;
    bool isMovableKing()                    const;

    std::vector<const Piece*> piecesAccessingSquare(Coordinates to) const;
    std::vector<const Piece*> piecesAbleToMove()                    const;
    std::vector<Coordinates>  kingsAccessibleSquares()              const;

    void removePiece(const Piece* p);


    Coordinates kingCoord() const { return _king->coord(); }
    Color       color()     const { return _color; }
    Board*      board()     const { return _board; }

private:
    static constexpr auto pawns = 8;
    static constexpr auto allPiecesExceptKing = 15;

    Board*       _board;
    const Color  _color;
    bool         _isCastled{ false };

    mutable std::optional<Move> _validatedMove;
    mutable std::optional<Move> _validatedCastling;

    template <std::size_t N>
    using Pieces = std::array<std::unique_ptr<Piece>, N>;

    Pieces<allPiecesExceptKing> _pieces;
    std::unique_ptr<Piece>      _king;

    const Piece* leftRook;
    const Piece* rightRook;

    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
};
}
