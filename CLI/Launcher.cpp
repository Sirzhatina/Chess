#include "Launcher.hpp"
#include <iostream>

Launcher::err_code Launcher::launch()
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

void Launcher::startMenu()
{
    char choice;
    while (true)
    {
        _dr->drawMainMenu();
        (std::cin >> choice).get();

        switch (choice)
        {
        case '1':
            play();
            break;
        case '2':
            dr->drawSettingsMenu();
            break;
        case '3':
            system("pause");
            return;
        default:
            continue;
        }
    }
}

void Launcher::play()
{
    try
    {
        _gp.start();
    }    
    catch(const IGameplayHandler::ExitCase& e)
    {
        std::cerr << e.byeMsg() << '\n';
    }
}
    