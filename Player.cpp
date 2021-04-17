//
// Created by Sirzh on 15.04.2021.
//

#include "Player.h"


Player::Player(color c): pieceClr(c) {


    Vertical startOfPawns = pieceClr == color::WHITE ? Vertical::two : Vertical::seven;
    Vertical startOfOthers = pieceClr == color::WHITE ? Vertical::one : Vertical::eight;

    unsigned alongLine = 1;
    for (auto& pwn: pawn) {
        pwn = std::make_unique<Pawn>( Coordinates{ Horizontal(alongLine++), startOfPawns } );
    }

    alongLine = 0;
    for (unsigned i = 0, inc = 1; i < PAIR_PIECES; i++, alongLine += 6, inc *= -1) {

        rook[i] = std::make_unique<Rook>( Coordinates{ Horizontal(alongLine += inc), startOfOthers } );
        knight[i] = std::make_unique<Knight>( Coordinates{ Horizontal(alongLine += inc), startOfOthers } );
        bishop[i] = std::make_unique<Bishop>( Coordinates{ Horizontal(alongLine += inc), startOfOthers } );
    }

    // Queen prefers corresponding color
    queen = std::make_unique<Queen>( Coordinates{ Horizontal::D, startOfOthers } );
    king = std::make_unique<King>( Coordinates{ Horizontal::E, startOfOthers } );


}