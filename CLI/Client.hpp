#pragma once

#include <memory>

#include <Core/Gameplay.hpp>

#include "Drawer.hpp"
#include "InputHandler.hpp"
#include <IDrawer.hpp>
#include <IClient.hpp>

class Client : public IClient
{
private:
    std::unique_ptr<Chess::Gameplay> _gp;

    void startMenu();
    void play();

public:
    Client(): IClient(std::make_shared<Drawer>()) {}
    
    err_code launch() override;
};
