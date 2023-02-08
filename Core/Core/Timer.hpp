#pragma once

#include <chrono>
#include <mutex>

template <class DurationUnits>
class Timer
{
public:

    template <class Duration = std::chrono::seconds>
    Timer(Duration&& d = Duration{0})
    : m_expired{true}
    , m_suspended{false}
    , m_start{std::chrono::system_clock::time_point{}}
    , m_duration{std::chrono::duration_cast<DurationUnits>(std::forward<Duration&&>(d))}
    {

    }

    auto& operator=(Timer&& t)
    {
        m_expired  = t.m_expired;
        m_start    = t.m_start;
        m_duration = t.m_duration;

        return *this;
    }

    void start() 
    {
        std::lock_guard lock{m_mtx};
        if (m_expired)
        {
            m_start = std::chrono::system_clock::now(); 
            m_expired = false;
        }
    }

    void stop()
    {
        m_start = {};
        m_expired = true;
    }

    bool isExpired()   const { return m_expired;   }
    bool isSuspended() const { return m_suspended; }

    void suspend() { m_suspended = true;  }
    void resume()  
    {
        if (!m_expired && m_suspended)
        {
            m_start = std::chrono::system_clock::now(); 
            m_suspended = false; 
        }
    }

    void wait() 
    {
        // waiting for suspended timer lasts forever and essentially doesn't make sense
        if (m_suspended) return;
        if (!m_expired)
        {
            m_duration =- remainingImpl();
            std::this_thread::sleep_for(m_duration <= 0 ? DurationUnits{0} : m_duration);
            m_expired = true;
        }
    }

    DurationUnits remainingTime()
    {
        if (m_suspended)
        {
            return m_duration;
        }
        if (!m_expired)
        {
            m_duration =- remainingImpl();
            
            m_expired = m_duration <= DurationUnits{0};

            return m_expired ? DurationUnits{0} : m_duration;
        }
        return DurationUnits{0};
    }

private:

    bool m_expired;
    bool m_suspended;
    std::chrono::system_clock::time_point m_start;
    DurationUnits                         m_duration;

    std::mutex m_mtx;

    DurationUnits remainingImpl() const
    {
        return std::chrono::duration_cast<DurationUnits>(std::chrono::system_clock::now() - m_start);
    }
};
