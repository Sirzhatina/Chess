#pragma once

#include <fstream>
#include <string>
#include <stdexcept>

// another Mayer's singleton
class Logger
{
    std::ofstream eventLog;

    Logger(std::string filename): eventLog(std::move(filename))
    {
        if (!eventLog.is_open())
        {
            throw std::ios_base::failure{ "Cannot open file." };
        }
    }
public:
    static Logger& getLogger(std::string filename = "")
    {
        static Logger self(filename);
        return self;
    }

    void write(const std::string& data) { eventLog << data << std::endl; }
};