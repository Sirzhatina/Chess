#include "CLient.hpp"
#include "InputHandler.hpp"
#include "MatchSettingsIO.hpp"
#include <iostream>

Client::err_code Client::launch()
{
    try
    {
        mainMenuLoop();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return err_code::err;
    }
    return err_code::ok;
}

void Client::mainMenuLoop()
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
            settingsMenuLoop();
            break;
        case 'q':
            return;
        default:
            continue;
        }
    }   
}

void Client::settingsMenuLoop()
{
    std::unique_ptr<ISettingsIO> settings;
    char choice;
    while (true)
    {
        settings.reset();
        _dr->drawSettingsMenu();
        std::cin >> choice;
        while (std::cin.get() != '\n');

        switch (choice)
        {
        case '1':
            settings = std::make_unique<MatchSettingsIO>();
            break;
        case 'q':
            return;
        default:
            continue;
        }
        settings->showSettings();
        settings->inputSettings();
    }
}


void Client::play()
{
    _gp = std::make_unique<Chess::Match>(_dr, std::make_shared<InputHandler>());
    try
    {
        _gp->start();
    }
    catch(const IInputHandler::ExitCase& e)
    {
        std::cerr << e.byeMsg() << '\n';
    }
    _gp.reset(nullptr);
}
