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
    Drawer() = default;

    void drawMainMenu()     const override;
    void drawSettingsMenu() const override { /* dummy method for being implemented in future */ }
    // draws all widgets except the board itself which the IGameplayHandler is responsible for,
    // so in console implementation, does nothing essential
    void drawPlay()         const override { system(clear); }
};