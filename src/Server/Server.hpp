#pragma once

#include <asio.hpp>
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

    Server(std::uint16_t port);

    StateCode run();

    StateCode currentState() const { return m_currentState; }

private:
    using Client = std::unique_ptr<asio::ip::tcp::socket>;

    static constexpr Seconds defaultAwaiting = 1;
    static constexpr std::size_t RESERVED_CLIENTS = 64;

    std::uint16_t m_port;
    Seconds       m_eventAwaiting{defaultAwaiting};

    std::vector<Client> m_clients{RESERVED_CLIENTS};

    asio::ip::tcp::acceptor m_acceptor;

    asio::io_context io;

    bool m_isWaiting{true};

    StateCode m_currentState;

private:
    void acceptionHandler();

    void onAcceptor();
    void onClient();

    void onReady();

    void onDisconnection();
    
    void updateStateFromCLI();

    void waitForEvents();
};