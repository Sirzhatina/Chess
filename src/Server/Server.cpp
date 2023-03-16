#include <future>
#include "Server.hpp"

void Server::run()
{
    m_acceptor.listen(m_port);

    auto futureRes = std::async(std::launch::async, [this]{ waitForEvents(); });

    // something like
    // AdminCLI cli;
    // cli.manage(this);

    futureRes.get();
}

void Server::waitForEvents()
{
    while (m_isWaiting)
    {
        if (m_selector.wait(sf::seconds(m_eventAwaiting)))
        {
            onReady();
        }
        updateFromCLI();
    }
}

void Server::onReady()
{
    if (m_selector.isReady(m_acceptor))
    {
        onAcceptor();
    }
    else
    {
        onClient();
    }
}

void Server::onAcceptor()
{
    m_clients.emplace_back(std::make_unique<sf::TcpSocket>());
    try
    {
        acceptionHandler(m_acceptor.accept(*m_clients.back()));   
    }
    catch(const std::runtime_error& e)
    {
        m_clients.pop_back();
        throw e;
    }
    m_selector.add(*m_clients.back());
}

// void Server::onClient()
// {
//     for (auto&& client : m_clients) {}
// }

void Server::acceptionHandler(sf::Socket::Status s)
{
    using enum sf::Socket::Status;
    switch (s)
    {
    case Error:        throw std::runtime_error{"Error when connecting occured"};
    case Disconnected: throw std::runtime_error{"Disconnected"};
    default:           break;
    }
}