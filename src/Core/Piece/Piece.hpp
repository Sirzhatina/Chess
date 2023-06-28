//
// Created by Sirzh on 15.04.2021.
//

#pragma once

#include "..\Primitives.hpp"
#include <vector>

namespace Chess
{
class Player;

/// @brief Abstract class representing chess piece and implementing some low-level algorithms that are applied
///        to individual pieces. If higher-level algorithms, applicable to pieces' interaction, are needed, 
///        check Player and Match classes
class Piece
{
    const Player* _player;
    Coordinates   _currentCoord;
    bool          _firstMove{ true };

protected:
    /// @brief Inspects whether a piece standing on the passed coordinates belongs
    ///        to the same player that owns this piece.
    /// @param square Coordinates to inspect
    /// @return True if a piece on the square belongs to the same player as this, false otherwise.
    ///         Method also returns false if the square is empty
    bool isFriendlySquare(Coordinates square) const;

    /// @brief Inspects whether the passed coordinates are of this piece
    /// @param square Coordinates to compare piece's with
    /// @return True if current piece coordinates equal to square, false otherwise
    bool isSameSquare(Coordinates square) const;

    /// @brief Method reports whether this piece is able to reach given coordinates according to the game rules, 
    ///        but does it without considering obstacles (see isClearRoute).
    ///        Method shouldn't be called directly and only used inside isPossibleMove
    /// @param to Coordinates to reach
    /// @return True if between two coordinates (piece's current and passed), 
    ///         it is possible to construct a route with respect to rules of the game, false otherwise.
    virtual bool isValidRoute(Coordinates to) const = 0;

    /// @brief Method reports whether this piece has obstacles on its route. 
    ///        Method doesn't check the passed parameter 
    ///        and it shouldn't be called directly, as well as isValidRoute
    /// @param to Coordinates to reach
    /// @return True if between this piece's coordinates and to there aren't any other pieces, false otherwise.
    ///         For Knight, Pawn and King, always returns true 
    ///         If called without route validation, method can work wrong.
    virtual bool isClearRoute(Coordinates to) const = 0;
public:
    /// @brief Trivially constructs the piece and its data members from arguments
    /// @param p Player owning this piece
    /// @param coord Initial coordinates
    Piece(const Player* p, Coordinates coord);
    
    virtual ~Piece() = default;

    /// @brief The only method used for summary validation. It doesn't change piece's location, just
    ///        reports whether a chosen route is correct. To actually designate coordinates to the piece,
    ///        use setCoordinates()
    /// @param to Coordinates to potentially move to
    /// @return True if route is correct and no obstacles on it, false otherwise
    bool isPossibleMove(Coordinates to) const;

    /// @brief Informs about whether the piece isn't blocked by other pieces or board borders
    /// @return True if piece is able to move at least to 1 square, false otherwise
    virtual bool isAbleToMove() const = 0;
    
    /// @brief Sets new coordinates to this pieces
    /// @param to Coordinates to set
    void setCoordinates(Coordinates to);

    /// @brief Method verifies that the coordinates to reach to are withing borders
    ///        And the piece can move there. Firsly, the method is a helper for isAbleToMove().
    /// @param to Coordinates to reach
    /// @param x Shift on x
    /// @param y Shift on y
    /// @return True if {to.x + x, to.y + y} is a correct coordinates and the piece can move there, false otherwise
    bool isAbleToMoveToSqr(Coordinates to, int x, int y) const;

    const Player* player()      const { return _player; }
    Coordinates   coord()       const { return _currentCoord; }
    bool          isFirstMove() const { return _firstMove; }
};
}
