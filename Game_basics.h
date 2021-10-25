//
// Created by Sirzh on 16.04.2021.
//

#ifndef CHESS_GAME_BASICS_H
#define CHESS_GAME_BASICS_H

#include "Msoftcon.h"
#include "Gameplay.h"
#include "IObserver.h"

// concrete observer
class Game_basics : public IObserver {
    void draw() const;

    char getPieceKind(const Chess::Piece*) const;
    void drawLine(Chess::Vertical line) const;
    void drawReversedLine(Chess::Vertical line) const;
    
    void play();

public:
    Game_basics() { init_graphics(); }
    int run();

    void handleEvent(const Chess::Gameplay* observed) override;
};


#endif //CHESS_GAME_BASICS_H
