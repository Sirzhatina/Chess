#pragma once

#include <memory>
#include "IDrawer.hpp"

class IMenu;

class IClient
{
public:
    enum class err_code { ok, err };

    IClient(std::unique_ptr<IMenu> m): m_menu(std::move(m)) { }
    
    virtual ~IClient() = default;

    virtual err_code launch() = 0;

protected:
    std::unique_ptr<IMenu>   m_menu;
};
