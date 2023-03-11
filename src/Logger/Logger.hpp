#pragma once

#include <fstream>
#include <string>
#include <stdexcept>

class Logger
{
public:
    static constexpr auto filename = "log.txt";

private:
    std::ofstream eventLog;

    Logger(std::string filename): eventLog(std::move(filename), std::ios_base::app)
    {
        if (!eventLog.is_open())
        {
            throw std::ios_base::failure{ "Cannot open file." };
        }
    }
public:
    static Logger& getLogger()
    {
        static Logger self(filename);
        return self;
    }

    void write(const std::string& data) { eventLog << data << std::endl; }
};