#include <iostream>
#include "CLI.hpp"
#include "Drawer.hpp"
#include <Core/Player.hpp>

void Drawer::drawMainMenu() const
{
    system(CLI::clear);

    // 10 positions down from left up corner
    std::cout << "\n\n\n\n\n\n\n\n\n\n";

    CLI::tab(); std::cout << "\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
    CLI::tab(); std::cout << "\t\t*           WELCOME TO THE BEST GAME YOU'VE EVER            *\n";
    CLI::tab(); std::cout << "\t\t*                        EXPERIENCED                        *\n";
    CLI::tab(); std::cout << "\t\t*                                                           *\n";
    CLI::tab(); std::cout << "\t\t*                  Choose the option below                  *\n";
    CLI::tab(); std::cout << "\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
    std::cout << "\n\n";
    CLI::tab(); std::cout << "\t\t1 - Play.\n";
    CLI::tab(); std::cout << "\t\t2 - Settings (not implemented).\n";
    CLI::tab(); std::cout << "\t\t3 - Quit.\n";
    CLI::tab(); std::cout << "\t\tInput: ";
}
