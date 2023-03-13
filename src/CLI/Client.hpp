#pragma once

#include <memory>

#include <Core/Match.hpp>

#include "Drawer.hpp"
#include <Interfaces/IDrawer.hpp>
#include <Interfaces/IClient.hpp>

class Client : public IClient
{
private:
    std::unique_ptr<Chess::Match> m_gameplay;

    void mainMenuLoop();
    void settingsMenuLoop();

    void play();

public:
    Client(): IClient(std::make_shared<Drawer>()) {}
    
    err_code launch() override;
};
