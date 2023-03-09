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
protected:
    // std::atomic<bool> m_moveRetrieved{false};

    // class AtomicRAII
    // {
    //     IInputHandler* m_withAtomic;
    // public:
    //     AtomicRAII(IInputHandler* withAtomic): m_withAtomic(withAtomic) { m_withAtomic->m_moveRetrieved.store(false); }
    //     ~AtomicRAII() { m_withAtomic->m_moveRetrieved.store(true); }
    // };

public:
    virtual MoveResult getMove() = 0;

    // bool isMoveRetrieved() const { return m_moveRetrieved.load(); }
        
    virtual ~IInputHandler() = default;
};
