#pragma once


#include <future>
#include <atomic>

namespace Chess { struct Move; }
class IInputHandler
{
protected:
    std::atomic<bool> m_moveRetrieved{false};

    class AtomicRAII
    {
        IInputHandler* m_withAtomic;
    public:
        AtomicRAII(IInputHandler* withAtomic): m_withAtomic(withAtomic) { m_withAtomic->m_moveRetrieved.store(false); }
        ~AtomicRAII() { m_withAtomic->m_moveRetrieved.store(true); }
    };

public:
    virtual std::future<Chess::Move> getMove() = 0;

    bool isMoveRetrieved() const { return m_moveRetrieved.load(); }
        
    virtual ~IInputHandler() = default;

    class ExitCase;
};

class IInputHandler::ExitCase
{
    const char* byeMessage;
public:
    ExitCase(const char* bye): byeMessage{bye} { }

    virtual const char* byeMsg() const { return byeMessage; }
};