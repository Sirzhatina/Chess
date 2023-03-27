#include "AdminCLI.hpp"
#include "Server.hpp"
#include <regex>
#include <future>

AdminCLI::AdminCLI(std::unique_ptr<Server> managed): m_managed{std::move(managed)} { }

void AdminCLI::manage()
{
    auto fut = std::async(std::launch::async, [this]{ return m_managed->run(); });

    std::cout << "Ready to take commands.\n";
    std::string input;

    while (m_managed->m_isWaiting)
    {
        std::getline(std::cin, input);

        updateServerState(input);
    }

    if (fut.get() == Server::StateCode::unexpectedBevahior)
    {
        std::cerr << "Error during execution occured.\n";
    }
}

void AdminCLI::updateServerState(const std::string& cmd)
{
    if (cmd == "stop")
    {
        m_managed->m_isWaiting = false;
    }
    else if (std::regex_match(cmd, std::regex("change [0-9]+")))
    {
        m_managed->m_eventAwaiting = Server::Seconds(std::stoul(cmd.substr(cmd.find_first_of("0123456789"))));
    }
    else
    {
        std::cout << "Unknown command.\n";
    }
}