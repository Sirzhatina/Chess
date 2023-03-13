#pragma once

#include "IDrawer.hpp"
#include <memory>

class IMenu
{
protected:
    std::shared_ptr<IDrawer> m_drawer;
public:
    IMenu(std::shared_ptr<IDrawer> dr): m_drawer{dr} { }

    virtual void toMainMenu()     const = 0;
    virtual void toSettingsMenu() const = 0;
    virtual void toGameplay()     const = 0;
};