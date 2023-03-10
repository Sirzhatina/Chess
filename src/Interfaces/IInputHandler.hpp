#pragma once

#include <future>
#include <atomic>
#include <variant>

namespace Chess  { struct Move; }

class IInputHandler
{
public:
    enum class QuitToken : std::uint8_t { };

    using MoveResult = std::future<std::variant<Chess::Move, QuitToken>>;

public:
    virtual MoveResult getMove() = 0;
        
    virtual ~IInputHandler() = default;
};
