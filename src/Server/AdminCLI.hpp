#pragma once

#include <iostream>
#include <array>
#include <memory>

class Server;

class AdminCLI
{
private:
    std::unique_ptr<Server> m_managed;

    static constexpr std::array commands
    {
        "stop",
        "change"
    };

    void updateServerState(const std::string& cmd);

public:
    AdminCLI(std::unique_ptr<Server> managed);

    void manage();
};