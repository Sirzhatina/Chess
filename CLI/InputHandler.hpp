#pragma once


#include <IInputHandler.hpp>
#include <Core/Primitives.hpp>

class InputHandler : public IInputHandler
{
    static constexpr auto quitCommand = "quit";
    bool wantToQuit() const;

public:
    InputHandler() = default;

    std::optional<Chess::Move> getMove() const override;
};
