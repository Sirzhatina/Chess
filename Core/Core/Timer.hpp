#pragma once

#include <chrono>
#include <mutex>

template <class DurationUnits>
class Timer
{
public:
    
    template <class Duration>
    static Timer makeTimer(Duration&& d);

    bool start();

    void stop();

    void wait();

    std::chrono::duration<DurationUnits> remainingTime();

private:

    Timer() = default;

    bool m_expired;
    std::chrono::system_clock::time_point   m_start;
    std::chrono::duration<DurationUnits>    m_duration;

    std::mutex m_mtx;

    std::chrono::duration<DurationUnits> remainingImpl() const
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
static Timer<DurationUnits> Timer<DurationUnits>::makeTimer(Duration&& d)
{
    return 
    {
        true,
        std::chrono::system_clock::time_point{}, 
        std::chrono::duration_cast<DurationUnits>(std::forward<Duration&&>(d))
    };
}

template <class DurationUnits>
bool Timer<DurationUnits>::start() 
{
    std::lock_guard<std::mutex> lock(m_mtx);
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
        auto rem_t = remainingImpl();
        std::this_thread::sleep_for(m_duration <= rem_t ? {0} : rem_t);
        m_expired = true;
    }
}

template <class DurationUnits>
std::chrono::duration<DurationUnits> Timer<DurationUnits>::remainingTime()
{
    if (!m_expired)
    {
        auto rem_t = remainingImpl();
        
        m_expired = m_duration <= rem_t;

        return m_expired ? {0} : rem_t;
    }
    return {0};
}