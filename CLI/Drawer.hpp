#pragma once

#include <IDrawer.hpp>
#include "BoardDrawer.hpp"

class Drawer : public IDrawer
{
    std::shared_ptr<const BoardDrawer> boardDrawer_{new BoardDrawer{}};
public:
    Drawer() = default;

    void drawMainMenu()     const override;
    void drawSettingsMenu() const override { /* dummy method for being implemented in future */ }
    void drawPlay()         const override { /* just a placeholder: in the current implementation, drawBoard() is enough */ }

    std::shared_ptr<const IBoardDrawer> getBoardDrawer() const override { return boardDrawer_; }
};