//
// Created by Sirzh on 16.04.2021.
//

#pragma once

#include "Msoftcon.h"
#include <stdexcept>
#include <Core\Board.hpp>
#include <Core\Gameplay.hpp>
#include <Core\IGameplayHandler.hpp>

class Game_basics : public IGameplayHandler
{
    void draw() const;

    char getPieceKind(const Chess::Piece*) const;
    void drawLine(Chess::Vertical line) const;
    void drawReversedLine(Chess::Vertical line) const;

    void play();

    Chess::Gameplay _gameplay;

public:
    Game_basics(): _gameplay(this) { init_graphics(); }
    int run();

    Chess::Move getMove() const override;
    void drawBoard(const Chess::Board* board) override;

};

class ExitCase : public std::runtime_error
{
public:
    ExitCase(const char* byeMsg) : std::runtime_error{ byeMsg } { }
};
