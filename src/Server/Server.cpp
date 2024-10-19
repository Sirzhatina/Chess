#include <iostream>
#include "Server.hpp"
#include "AdminCLI.hpp"

Server::Server(std::uint16_t port) 
    : m_port{ port }
    , m_currentState{ StateCode::stopped }
    , m_acceptor{io} {

}

Server::StateCode Server::run()
{
    m_currentState = StateCode::inWork;
    m_acceptor.listen(m_port);

    try
    {
        waitForEvents();
    }
    catch(const std::exception& e)
    {
        m_currentState = StateCode::unexpectedBevahior;
    }
    return m_currentState;
}

// TODO: implement the method
void Server::waitForEvents()
{
    while (false)
    {
        if (false)
        {
            onReady();
        }
        updateStateFromCLI();
    }
    onDisconnection();
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
    if (true)
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
    try
    {
        //acceptionHandler(m_acceptor.accept(*m_clients.back()));   
    }
    catch(const std::runtime_error& e)
    {
        m_clients.pop_back();
        throw e;
    }
    //m_selector.add(*m_clients.back());
}

void Server::onClient()
{
    for (auto&& client : m_clients) {}
}

void Server::acceptionHandler()
{
}

void Server::onDisconnection()
{
    for (auto&& client : m_clients)
    {
        // TODO: Notify the peer on disconnecting
        //client->disconnect();
    }
}