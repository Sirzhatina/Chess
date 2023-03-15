#pragma once

#include <Interfaces/IMenu.hpp>
#include <memory>
#include "Drawer.hpp"

class Menu : public IMenu
{
public:
    Menu(): IMenu(std::make_shared<Drawer>()) { }
    
    void toMainMenu()     const override;
    void toSettingsMenu() const override;
    void toGameplay()     const override;
};