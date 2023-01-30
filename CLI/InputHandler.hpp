#pragma once


#include <Core/IInputHandler.hpp>
#include <Core/Primitives.hpp>

class InputHandler : public IInputHandler
{
    static constexpr auto quitCommand = "quit";
    bool wantToQuit() const;

public:
    InputHandler() = default;

    Chess::Move getMove() const override;
};
