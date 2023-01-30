#include "CLient.hpp"
#include <iostream>

Client::err_code Client::launch()
{
    try
    {
        startMenu();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return err_code::err;
    }
    return err_code::ok;
}

void Client::startMenu()
{
    char choice;
    while (true)
    {
        _dr->drawMainMenu();
        std::cin >> choice;
        while (std::cin.get() != '\n');

        switch (choice)
        {
        case '1':
            play();
            break;
        case '2':
            _dr->drawSettingsMenu();
            break;
        case '3':
            return;
        default:
            continue;
        }
    }
}

void Client::play()
{
    _gp = std::make_unique<Chess::Gameplay>(_dr->getBoardDrawer(), std::make_shared<InputHandler>());   
    try
    {
        _gp->start();
    }
    catch(const IInputHandler::ExitCase& e)
    {
        std::cerr << e.byeMsg() << '\n';
    }
    _gp.reset();
}
    