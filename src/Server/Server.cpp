#include <future>
#include <iostream>
#include "Server.hpp"
#include "AdminCLI.hpp"

Server::StateCode Server::run()
{
    m_currentState = StateCode::inWork;
    m_acceptor.listen(m_port);

    auto futureRes = std::async(std::launch::async, [this]{ waitForEvents(); });

    AdminCLI managing(this);
    managing.manage();

    try
    {
        futureRes.get();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        m_currentState = StateCode::unexpectedBevahior;
    }
    
    return m_currentState;
}

void Server::waitForEvents()
{
    while (m_isWaiting)
    {
        if (m_selector.wait(sf::seconds(m_eventAwaiting)))
        {
            onReady();
        }
        updateStateFromCLI();
    }
}

void Server::updateStateFromCLI()
{
    if (!m_isWaiting)
    {
        m_currentState = StateCode::stopped;
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