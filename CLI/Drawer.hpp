#pragma once

#include <IDrawer.hpp>
#include "BoardDrawer.hpp"

class Drawer : public IDrawer
{
    std::shared_ptr<const BoardDrawer> boardDrawer_{new BoardDrawer{}};
public:
    Drawer() = default;

    void drawMainMenu()     const override;
    void drawSettingsMenu() const override;
    void drawPlay()         const override { /* just a placeholder: in the current implementation, drawBoard() of boardDrawer is enough */ }

    std::shared_ptr<const IBoardDrawer> getBoardDrawer() const override { return boardDrawer_; }
};