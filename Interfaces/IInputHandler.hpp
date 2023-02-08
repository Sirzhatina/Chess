#pragma once

#include <Core/Primitives.hpp>
#include <future>
#include <atomic>

class IInputHandler
{
protected:
    std::atomic<bool> m_moveRetrieved{false};

public:
    virtual std::future<Chess::Move> getMove() = 0;

    bool isMoveRetrieved() const { return m_moveRetrieved.load(); }
        
    virtual ~IInputHandler() = default;

    class ExitCase;
};

class IInputHandler::ExitCase
{
    const char* byeMessage;
public:
    ExitCase(const char* bye): byeMessage{bye} { }

    virtual const char* byeMsg() const { return byeMessage; }
};