#pragma once

#include <memory>

#include <Core/Gameplay.hpp>

#include "Drawer.hpp"
#include "InputHandler.hpp"
#include "IDrawer.hpp"
#include "ILauncher.hpp"

class Launcher : public ILauncher
{
private:
    std::unique_ptr<Chess::Gameplay> _gp;

    void startMenu();
    void play();

public:
    Launcher(): ILauncher(std::make_shared<Drawer>()) {}
    
    err_code launch() override;
};
