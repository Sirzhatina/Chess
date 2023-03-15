#include <iostream>
#include <memory>
#include <Core/Match.hpp>
#include <Core/Settings.hpp>
#include "MatchSettingsIO.hpp"
#include "InputHandler.hpp"

#include "Menu.hpp"

void Menu::toMainMenu() const
{
    char choice;
    while (true)
    {
        m_drawer->drawMainMenu();
        std::cin >> choice;
        while (std::cin.get() != '\n');

        switch (choice)
        {
        case '1':
            toGameplay();
            break;
        case '2':
            toSettingsMenu();
            break;
        case 'q':
            return;
        default:
            continue;
        }
    }  
}

void Menu::toSettingsMenu() const
{
    std::unique_ptr<ISettingsIO> settings;
    char choice;
    while (true)
    {
        settings.reset();
        m_drawer->drawSettingsMenu();
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

void Menu::toGameplay() const
{
   auto gameplay = std::make_unique<Chess::Match>(m_drawer, std::make_shared<InputHandler>());

    m_drawer->drawEndgame(gameplay->start());
}