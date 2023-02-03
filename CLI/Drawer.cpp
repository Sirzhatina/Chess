#include <iostream>
#include "CLI.hpp"
#include "Drawer.hpp"

#include <Core/Settings.hpp>

void Drawer::drawMainMenu() const
{
    system(CLI::clear);
    using std::cout;

    cout << CLI::down();

    cout 
        << CLI::dTab() << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n"
        << CLI::dTab() << "*           WELCOME TO THE BEST GAME YOU'VE EVER            *\n"
        << CLI::dTab() << "*                        EXPERIENCED                        *\n"
        << CLI::dTab() << "*                                                           *\n"
        << CLI::dTab() << "*                  Choose the option below                  *\n"
        << CLI::dTab() << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n"
        << "\n\n"

        << CLI::dTab() << "1 - Play.\n"
        << CLI::dTab() << "2 - Settings.\n"
        << CLI::dTab() << "q - Quit.\n"
        << CLI::dTab() << "Input: ";
}

void Drawer::drawSettingsMenu() const
{

    system(CLI::clear);
    CLI::down();
    CLI::dTab(); std::cout << "[SETTINGS]\n";
    CLI::dTab(); std::cout << "1 - Match\n";
    CLI::dTab(); std::cout << "q - Back to main menu\n";
}
