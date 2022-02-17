//
// Created by Sirzh on 15.04.2021.
//

#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H

#include <vector>
#include "Primitives.h"
#include "Piece/Piece.h"
#include "Board.h"

namespace Chess 
{
class Player {

    static constexpr auto PAWNS = 8;
    static constexpr auto PAIR_PIECES = 2;

    bool check{ false };
    bool checkmate{ false };

    Board* board;
    const Color color;

    Piece* pawn[PAWNS];

    Piece* knight[PAIR_PIECES];
    Piece* bishop[PAIR_PIECES];
    Piece* rook[PAIR_PIECES];

    Piece* queen;
    Piece* king;

    bool possibleCastling(Coordinates to) const;
    void castling(Coordinates to);

    bool friendlySquare(Coordinates to) const { return board->getPiece(to) ? board->getPiece(to)->getPlayer() == this : false; }

public:
    Player(Board* b, Color c);

    Piece* move(Coordinates from, Coordinates to);

    std::vector<Piece*> piecesAccessingSquare(Coordinates to) const;
    bool                isAccessedSquare(Coordinates to)      const;
    
    void setCheck(bool ch) { check = ch; }
    void setCheckmate(bool ch) { checkmate = ch; }

    bool isAbleToMove() const;

    Color       getColor()     const { return color; }
    Board*      getBoard()     const { return board; }
    Coordinates getKingCoord() const { return king->getCoord(); }
    bool        isCheck()      const { return check; }
    bool        isCheckmate()  const { return checkmate; }

    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
};
}
#endif //CHESS_PLAYER_H
