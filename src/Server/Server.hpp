#pragma once

#include <SFML/Network.hpp>
#include <vector>
#include <memory>

class Server
{
public:
    friend class AdminCLI;
    using Seconds = std::uint16_t;

    enum class StateCode
    {
        stopped,
        inWork,
        unexpectedBevahior
    };

    Server(std::uint16_t port) : m_port{port}, m_currentState{StateCode::stopped} { m_selector.add(m_acceptor); }

    StateCode run();

    StateCode currentState() const { return m_currentState; }

private:
    using Client = std::unique_ptr<sf::TcpSocket>;

    static constexpr Seconds defaultAwaiting = 1;

    std::uint16_t m_port;
    Seconds       m_eventAwaiting{defaultAwaiting};

    std::vector<Client> m_clients{64};

    sf::SocketSelector m_selector;
    sf::TcpListener    m_acceptor;

    bool m_isWaiting{true};

    StateCode m_currentState;

private:
    void acceptionHandler(sf::Socket::Status s);

    void onAcceptor();
    void onClient();

    void onReady();
    
    void updateStateFromCLI();

    void waitForEvents();
};