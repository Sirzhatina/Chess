//
// Created by Sirzh on 16.04.2021.
//

#ifndef CHESS_GAME_BASICS_H
#define CHESS_GAME_BASICS_H

#include "Gameplay.h"
#include "IObserver.h"

// concrete observer
class Game_basics : public IObserver {

    Gameplay game;

    void draw();
    void play();

public:
    Game_basics() { game.addObserver(this); }
    int run();

    void handleEvent(const Gameplay* observed) override;
};


#endif //CHESS_GAME_BASICS_H
