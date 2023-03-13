#pragma once

#include <memory>

#include <Core/Match.hpp>

#include "Drawer.hpp"
#include "Menu.hpp"
#include <Interfaces/IClient.hpp>

class Client : public IClient
{
public:
    Client(): IClient(std::make_unique<Menu>()) {}
    
    err_code launch() override;
};
