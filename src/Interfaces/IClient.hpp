#pragma once

#include <memory>
#include "IDrawer.hpp"

class IClient
{
public:
    enum class err_code { ok, err };

    IClient(std::shared_ptr<IDrawer> dr): m_drawer(dr) { }
    
    virtual err_code launch() = 0;

protected:
    std::shared_ptr<IDrawer> m_drawer;
};
