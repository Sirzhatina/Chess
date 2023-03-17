#pragma once

#include <iostream>
#include <array>
#include <string>

class Server;

class AdminCLI
{
private:
    Server* m_managable;

    static constexpr std::array commands
    {
        "stop",
        "change"
    };

    void updateServerState(const std::string& cmd);

public:
    AdminCLI(Server* managable);

    void manage();
};