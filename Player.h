//
// Created by Sirzh on 15.04.2021.
//

#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H

#include <memory>
#include "Piece/Piece.h"
#include "Game_basics.h"

class Player {
    friend void Game_basics::play();

    enum class color { BLACK, WHITE };

    static constexpr auto PAWNS = 8;
    static constexpr auto PAIR_PIECES = 2;

    color pieceClr;

    bool isChecked = false;
    bool isDefeated = false;


    std::unique_ptr<Pawn> pawn[PAWNS];

    std::unique_ptr<Knight> knight[PAIR_PIECES];
    std::unique_ptr<Bishop> bishop[PAIR_PIECES];
    std::unique_ptr<Rook> rook[PAIR_PIECES];

    std::unique_ptr<Queen> queen;
    std::unique_ptr<King> king;

public:
    Player(color c);


    bool Move(Coordinates from, Coordinates to);

    bool isUnderCheck() const { return isChecked; }
    bool isCheckMate() const { return isDefeated; }


    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
};


#endif //CHESS_PLAYER_H
