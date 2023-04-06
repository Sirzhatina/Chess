export module IInputHandler;

import std.core;
import std.threading;

namespace Core  { struct Move; }

export class IInputHandler
{
public:
    enum class QuitToken : std::uint8_t { };

    using MoveResult = std::future<std::variant<Core::Move, QuitToken>>;

public:
    virtual MoveResult getMove() = 0;
        
    virtual ~IInputHandler() = default;
};
