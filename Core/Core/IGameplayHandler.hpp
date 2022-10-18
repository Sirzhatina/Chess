#pragma once

#include "Primitives.hpp"
#include <memory>

namespace Chess { class Board; }

class IGameplayHandler
{
public:
    virtual Chess::Move getMove()                            const = 0;
    // resposible only for mapping the board to the window but not the whole possible window
    virtual void        drawBoard(std::shared_ptr<const Chess::Board> b) const = 0;

    virtual ~IGameplayHandler() = default;

    class ExitCase;
};

class IGameplayHandler::ExitCase
{
    const char* byeMessage;
public:
    ExitCase(const char* bye): byeMessage{bye} { }

    virtual const char* byeMsg() const { return byeMessage; }
};