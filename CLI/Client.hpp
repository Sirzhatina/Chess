#pragma once

#include <memory>

#include <Core/Match.hpp>

#include "Drawer.hpp"
#include <IDrawer.hpp>
#include <IClient.hpp>

class Client : public IClient
{
private:
    std::unique_ptr<Chess::Match> _gp;

    void mainMenuLoop();
    void settingsMenuLoop();

    void play();

public:
    Client(): IClient(std::make_shared<Drawer>()) {}
    
    err_code launch() override;
};
