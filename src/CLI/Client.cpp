#include "Client.hpp"
#include "InputHandler.hpp"
#include "MatchSettingsIO.hpp"
#include <iostream>

Client::err_code Client::launch()
{
    try
    {
        m_menu->toMainMenu();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return err_code::err;
    }
    return err_code::ok;
}

