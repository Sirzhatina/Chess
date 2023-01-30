#pragma once

#include <IBoardDrawer.hpp>

class BoardDrawer : public IBoardDrawer
{
public:
    void drawBoard(std::shared_ptr<const Chess::Board> b) const override;
};