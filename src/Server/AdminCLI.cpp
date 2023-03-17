#include "AdminCLI.hpp"
#include "Server.hpp"
#include <regex>

AdminCLI::AdminCLI(Server* managable): m_managable{managable} { }

void AdminCLI::manage()
{
    std::cout << "Ready to take commands.\n";
    std::string input;

    while (m_managable->m_isWaiting)
    {
        std::getline(std::cin, input);

        updateServerState(input);
    }
}

void AdminCLI::updateServerState(const std::string& cmd)
{
    if (cmd == "stop")
    {
        m_managable->m_isWaiting = false;
    }
    else if (std::regex_match(cmd, std::regex("change [0-9]+")))
    {
        m_managable->m_eventAwaiting = Server::Seconds(std::stoul(cmd.substr(cmd.find_first_of("0123456789"))));
    }
    else
    {
        std::cout << "Unknown command.\n";
    }
}