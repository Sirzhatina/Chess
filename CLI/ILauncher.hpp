#pragma once

#include <memory>

#include "IDrawer.hpp"
#include <Core/IGameplayHandler.hpp>

class ILauncher
{
public:
    enum class err_code { ok, err };

protected:
    std::unique_ptr<IDrawer>            _dr;
    std::shared_ptr<IGameplayHandler>   _gpHandler;

public:
    ILauncher(std::unique_ptr<IDrawer> dr, std::shared_ptr<IGameplayHandler> gp): _dr(std::move(dr)), _gpHandler(gp) { }
    
    virtual err_code launch() = 0;
};