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

public:
    Drawer(const Chess::Gameplay* gp);

    void drawMainMenu()     const override;
    void drawSettingsMenu() const override { /* dummy method for being implemented in future */ }
    void drawBoard()        const override;
};