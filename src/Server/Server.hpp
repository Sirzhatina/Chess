#pragma once

#include <SFML/Network.hpp>
#include <vector>

class Server
{
    unsigned short m_port;

    std::vector<sf::TcpSocket> m_clients{64};

    sf::SocketSelector m_selector;
    sf::TcpListener    m_acceptor;

    void acceptionHandler(sf::Socket::Status s)
    {
        using enum sf::Socket::Status;
        switch (s)
        {
        case Error:        throw std::runtime_error{"Error when connecting occured"};
        case Disconnected: throw std::runtime_error{"Disconnected"};
        default: break;
        }
    }

public:
    Server(unsigned short port) : m_port{port}
    {
        m_selector.add(m_acceptor);
    }
    

    void run()
    {
        m_acceptor.listen(m_port);

        while (m_selector.wait())
        {
            if (m_selector.isReady(m_acceptor))
            {
                m_clients.push_back(sf::TcpSocket{});
                try
                {
                    acceptionHandler(m_acceptor.accept(m_clients.back()));   
                }
                catch(const std::runtime_error& e)
                {
                    m_clients.pop_back();
                    throw e;
                }

            }
            else
            {
                for (auto&& client : m_clients)
                {

                }
            }
        }
    }
};