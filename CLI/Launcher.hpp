#pragma once

#include <memory>

#include <Core/IGameplayHandler.hpp>
#include <Core/Gameplay.hpp>
#include "IDrawer.hpp"

template <class DerivedDrawer, class DerivedGameplayHandler>
class Launcher
{
public:
    enum class err_code { ok, err };
    
private:
    std::unique_ptr<IDrawer>          _dr;
    std::shared_ptr<IGameplayHandler> _gpHandler;

    Chess::Gameplay _gp;

public:
    Launcher(): _dr(std::make_unique<DerivedDrawer>(&_gp)), _gpHandler(std::make_shared<DerivedGameplayHandler>()), _gp(_gpHandler) { }

    err_code launch();
};