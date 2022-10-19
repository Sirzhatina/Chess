#pragma once


#include <Core/IInputHandler.hpp>
#include <Core/Primitives.hpp>

class InputHandler : public IInputHandler
{
    // void draw() const;

    // char getPieceKind(const Chess::Piece*) const;
    // void drawLine(Chess::Vertical line) const;
    // void drawReversedLine(Chess::Vertical line) const;


    static constexpr auto quitCommand = "quit";
    bool wantToQuit() const;

public:
    InputHandler() = default;

    Chess::Move getMove() const override;
};
