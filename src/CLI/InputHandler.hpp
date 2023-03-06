#pragma once

#include <Interfaces/IInputHandler.hpp>
#include <Core/Primitives.hpp>

class InputHandler : public IInputHandler
{
    static constexpr auto quitCommand = "quit";
    bool wantToQuit() const;

public:
    InputHandler() = default;

    std::future<Chess::Move> getMove() override;
};
