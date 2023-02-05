#pragma once

#include <IDrawer.hpp>
#include "BoardDrawer.hpp"

class Drawer : public IDrawer
{
    std::shared_ptr<const BoardDrawer> boardDrawer_{new BoardDrawer{}};

    void drawBoard(const Chess::Board& board) const override;

    void showRemainingTime(const Chess::Match& m) const;
public:
    Drawer() = default;

    void drawMainMenu()     const override;
    void drawSettingsMenu() const override;
    void drawPlay(const Chess::Match& match) const override;
};