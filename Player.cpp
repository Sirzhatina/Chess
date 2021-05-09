//
// Created by Sirzh on 15.04.2021.
//

#include "Player.h"
#include "Square.h"


Player::Player(color c): pieceClr(c) {


    Vertical startOfPawns = pieceClr == color::WHITE ? Vertical::two : Vertical::seven;
    Vertical startOfOthers = pieceClr == color::WHITE ? Vertical::one : Vertical::eight;

    unsigned alongLine = 1;
    for (auto& pwn: pawn) {
        pwn = std::make_shared<Pawn>( Square{ Horizontal(alongLine++), startOfPawns, pwn } );
    }

    alongLine = 0;
    for (unsigned i = 0, inc = 1; i < PAIR_PIECES; i++, alongLine += 6, inc *= -1) {

        rook[i] = std::make_shared<Rook>( Square{ Horizontal(alongLine += inc), startOfOthers, rook[i] } );
        knight[i] = std::make_shared<Knight>( Square{ Horizontal(alongLine += inc), startOfOthers, knight[i] } );
        bishop[i] = std::make_shared<Bishop>( Square{ Horizontal(alongLine += inc), startOfOthers, bishop[i] } );
    }

    // Queen prefers corresponding color
    queen = std::make_shared<Queen>( Square{ Horizontal::D, startOfOthers, queen } );
    king = std::make_shared<King>( Square{ Horizontal::E, startOfOthers, king } );


}