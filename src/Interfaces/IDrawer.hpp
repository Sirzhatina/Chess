#pragma once

#include <memory>
#include <Core/Match.hpp>

namespace Chess { class Board; }

class IDrawer
{
protected:
    virtual void drawBoard(const Chess::Board& board) const = 0;
public:
    IDrawer() = default;

    virtual ~IDrawer() = default;

    virtual void drawMainMenu()     const = 0;
    virtual void drawSettingsMenu() const = 0;
    
    virtual void drawMatchEnd(Chess::Match::Winner winner) const = 0;
    virtual void drawPlay(const Chess::Match& match)       const = 0;

};