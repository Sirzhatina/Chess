#pragma once

#include "Primitives.hpp"

namespace Chess { class Board; }

class IGameplayHandler
{
public:
    virtual Chess::Move getMove() const = 0;
    virtual void drawBoard(const Chess::Board* board) = 0;

    virtual ~IGameplayHandler() = default;
};