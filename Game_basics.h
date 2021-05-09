//
// Created by Sirzh on 16.04.2021.
//

#ifndef CHESS_GAME_BASICS_H
#define CHESS_GAME_BASICS_H

#include "Piece/Piece.h"
#include "Square.h"

class Game_basics {
    static bool convertCoord(char x, char y, Square& returned);

public:
    static int run();
    static void play();
    static void draw();
};


#endif //CHESS_GAME_BASICS_H
