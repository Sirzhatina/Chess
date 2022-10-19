#pragma once

#include <iostream>

#include "IDrawer.hpp"

class Drawer : public IDrawer
{
#ifdef _WIN32
    static constexpr auto clear = "cls";
#else
    static constexpr auto clear = "clear";
#endif

    void tab() const { std::cout << "\t\t"; }

public:
    Drawer() = default;

    void drawMainMenu()     const override;
    void drawSettingsMenu() const override { /* dummy method for being implemented in future */ }
    void drawPlay()         const override { /* just a placeholder: in the current implementation, drawBoard() is enough */ }
    
    void drawBoard(std::shared_ptr<const Chess::Board> b) const override;
};