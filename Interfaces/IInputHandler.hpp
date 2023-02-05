#pragma once

#include <Core/Primitives.hpp>

class IInputHandler
{
public:
    virtual std::optional<Chess::Move> getMove() const = 0;
        
    virtual ~IInputHandler() = default;

    enum class InputType { move, incorrect, quit };

    class ExitCase;
};

class IInputHandler::ExitCase
{
    const char* byeMessage;
public:
    ExitCase(const char* bye): byeMessage{bye} { }

    virtual const char* byeMsg() const { return byeMessage; }
};