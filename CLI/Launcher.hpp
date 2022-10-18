#pragma once

#include <memory>

#include <Core/IGameplayHandler.hpp>
#include <Core/Gameplay.hpp>
#include "IDrawer.hpp"
#include "ILauncher.hpp"

class Launcher : public ILauncher
{
private:
    std::unique_ptr<Chess::Gameplay> _gp;

    void startMenu();
    void play();

public:
    Launcher(): ILauncher(std::make_unique<Drawer>(_gp.get()), std::make_shared<GameplayHandler>()),  _gp(std::make_unique<Chess::Gameplay>(_gpHandler)) { }
    
    err_code launch() override;
};



void Launcher::play()
{

}