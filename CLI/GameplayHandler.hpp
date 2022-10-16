#pragma once

#include <iostream>
#include <memory>

#include <Core/IGameplayHandler.hpp>
#include <Core/Gameplay.hpp>
#include <Core/Piece/Piece.hpp>
#include <Core/Primitives.hpp>

#include "IDrawer.hpp"

class GameplayHandler : public IGameplayHandler
{
    // void draw() const;

    // char getPieceKind(const Chess::Piece*) const;
    // void drawLine(Chess::Vertical line) const;
    // void drawReversedLine(Chess::Vertical line) const;

    void play();

    std::unique_ptr<IDrawer> dr;
    Chess::Gameplay _gameplay;

public:
    GameplayHandler(): _gameplay(this), dr(std::make_unique<IDrawer>(&_gameplay)) { }
    int run();

    Chess::Move getMove()                            const                      override;
    void        drawBoard(const Chess::Board* board)                            override;
};