//
// Created by Sirzh on 16.04.2021.
//

#ifndef CHESS_GAME_BASICS_H
#define CHESS_GAME_BASICS_H

#include "Piece/Piece.h"

class Game_basics {
    static bool convertCoord(char x, char y, Coordinates& returned);

public:
    static int run();
    static void play();
};


#endif //CHESS_GAME_BASICS_H
