#pragma once

#include <Interfaces/IInputHandler.hpp>


class InputHandler : public IInputHandler
{
    static constexpr auto quitCommand = "quit";
    bool wantToQuit() const;

public:
    InputHandler() = default;

    MoveResult getMove() override;
};
