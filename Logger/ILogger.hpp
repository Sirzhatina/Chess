#pragma once


class ILogger
{
    ILogger() = default;

public:
    virtual ~ILogger() = default;

    static ILogger& getLogger();

};