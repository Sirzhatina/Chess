#include "InputHandler.hpp"

#include <iostream>
#include <string>


Chess::Move InputHandler::getMove() const
{
    std::string coord;

    std::cout << "Move: ";
    std::getline(std::cin, coord);
    
    if (coord == quitCommand && wantToQuit())
    {
        throw ExitCase{"Do svidanya, spasibo, prihodite eshche"};
    }

    Chess::Move result{ {coord[0] - 'a', coord[1] - '1'}, {coord[3] - 'a', coord[4] - '1'} };
    return result;
}

bool InputHandler::wantToQuit() const 
{
    std::cout << "Are you sure you want to quit the match? y/n: ";
    char choice = std::cin.get();

    while (std::cin.get() != '\n');

    return choice == 'y';
}
