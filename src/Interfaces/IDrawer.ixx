export module IDrawer;

import std.memory;
import Match;

namespace Core { class Board; }

export class IDrawer
{
protected:
    virtual void drawBoard(const Core::Board& board) const = 0;
public:
    IDrawer() = default;

    virtual ~IDrawer() = default;

    virtual void drawMainMenu()     const = 0;
    virtual void drawSettingsMenu() const = 0;
    
    virtual void drawEndgame(Core::Match::Winner winner) const = 0;
    virtual void drawGameplay(const Core::Match& match)  const = 0;

};