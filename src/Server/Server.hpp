#pragma once

#include <SFML/Network.hpp>
#include <vector>
#include <memory>

class Server
{
    friend class AdminCLI;
public:
    using Seconds = std::uint16_t;

    Server(std::uint16_t port) : m_port{port} { m_selector.add(m_acceptor); }

    void run();

    enum class StatusCode
    {
        inWork,
        stopped,
        timeout,
        unexpectedBevahior
    };

private:
    using Client = std::unique_ptr<sf::TcpSocket>;

    static constexpr Seconds defaultAwaiting = 1;

    std::uint16_t m_port;
    Seconds       m_eventAwaiting{defaultAwaiting};

    std::vector<Client> m_clients{64};

    sf::SocketSelector m_selector;
    sf::TcpListener    m_acceptor;

    bool m_isWaiting{true};

private:
    void acceptionHandler(sf::Socket::Status s);

    void onAcceptor();
    void onClient();

    void onReady();
    void onTimeout();
    
    void updateFromCLI();

    void waitForEvents();
};