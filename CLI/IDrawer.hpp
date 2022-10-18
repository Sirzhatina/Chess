#pragma once

#include <Core/Gameplay.hpp>

class IDrawer
{
    const Chess::Gameplay* _gp;
public:
    IDrawer(const Chess::Gameplay* gp): _gp{gp} { }

    virtual ~IDrawer() = default;

    virtual void drawMainMenu()     const = 0;
    virtual void drawSettingsMenu() const = 0;
    virtual void drawPlay()        const = 0;
};