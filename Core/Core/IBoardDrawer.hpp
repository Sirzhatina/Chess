#pragma once

#include <memory>

namespace Chess { class Board; }

class IBoardDrawer
{
public:
    virtual void drawBoard(std::shared_ptr<const Chess::Board> b) const = 0;

    virtual ~IBoardDrawer() = default;
};