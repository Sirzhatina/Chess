#pragma once


class IDrawer
{
public:
    IDrawer() = default;

    virtual ~IDrawer() = default;

    virtual void drawMainMenu()     const = 0;
    virtual void drawSettingsMenu() const = 0;
    virtual void drawPlay()         const = 0;
};