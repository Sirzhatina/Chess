#pragma once

#include "Primitives.hpp"

class IInputHandler
{
public:
    virtual Chess::Move getMove() const = 0;
        
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