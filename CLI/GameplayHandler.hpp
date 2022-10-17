#pragma once

#include <iostream>
#include <map>
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


public:
    GameplayHandler() = default;

    Chess::Move getMove()                            const                      override;
    void        drawBoard(const Chess::Board* board)                            override;
};