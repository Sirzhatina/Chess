#pragma once

#include <chrono>
#include <mutex>

template <class DurationUnits>
class Timer
{
public:
    
    Timer() = default;

    template <class Duration = std::chrono::seconds>
    Timer(Duration&& d = Duration{0});

    auto& operator=(Timer&& t);

    // It's not allowed to launch timer twice until it's finished - in that case, the function returns false; otherwise true
    bool start();

    void stop();

    void wait();

    DurationUnits remainingTime();

private:

    bool m_expired;
    std::chrono::system_clock::time_point m_start;
    DurationUnits                         m_duration;

    std::mutex m_mtx;

    DurationUnits remainingImpl() const
    {
        return std::chrono::duration_cast<DurationUnits>(std::chrono::system_clock::now() - m_start);
    }
};

/*
 * ***********************************************************************************************
 * ********                             I M P L E M E N T A T I O N                         ******
 * ***********************************************************************************************
*/

template <class DurationUnits>
template <class Duration>
Timer<DurationUnits>::Timer(Duration&& d)
: m_expired{true}
, m_start{std::chrono::system_clock::time_point{}}
, m_duration{std::chrono::duration_cast<DurationUnits>(std::forward<Duration&&>(d))}
{

}
template <class DurationUnits>
auto& Timer<DurationUnits>::operator=(Timer&& t)
{
    m_expired  = t.m_expired;
    m_start    = t.m_start;
    m_duration = t.m_duration;

    return *this;
}

template <class DurationUnits>
bool Timer<DurationUnits>::start() 
{
    std::lock_guard lock{m_mtx};
    if (m_expired)
    {
        m_start = std::chrono::system_clock::now(); 
        m_expired = false;
        
        return true;
    }
    return false;
}

template <class DurationUnits>
void Timer<DurationUnits>::stop()
{
    m_start = {};
    m_expired = true;
}

template <class DurationUnits>
void Timer<DurationUnits>::wait() 
{ 
    if (!m_expired)
    {
        m_duration =- remainingImpl();
        std::this_thread::sleep_for(m_duration <= 0 ? DurationUnits{0} : m_duration);
        m_expired = true;
    }
}

template <class DurationUnits>
DurationUnits Timer<DurationUnits>::remainingTime()
{
    if (!m_expired)
    {
        m_duration =- remainingImpl();
        
        m_expired = m_duration <= 0;

        return m_expired ? DurationUnits{0} : m_duration;
    }
    return DurationUnits{0};
}