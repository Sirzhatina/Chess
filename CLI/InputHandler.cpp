#include "InputHandler.hpp"

#include <iostream>
#include <string>


std::optional<Chess::Move> InputHandler::getMove() const
{
    std::string coord;

    std::cout << "Move: ";
    std::getline(std::cin, coord);

    std::optional<Chess::Coordinates> from, to;
        
    from = Chess::Coordinates::makeCoord(coord[0] - 'a', coord[1] - '1');
    to   = Chess::Coordinates::makeCoord(coord[3] - 'a', coord[4] - '1');
    
    if (coord == quitCommand && wantToQuit())
    {
        throw ExitCase{"Do svidanya, spasibo, prihodite eshche"};
    }

    if (!from || !to)
    {
        return {};
    }

    return {{*from, *to}};
}

bool InputHandler::wantToQuit() const 
{
    std::cout << "Are you sure you want to quit the match? y/n: ";
    char choice = std::cin.get();

    while (std::cin.get() != '\n');

    return choice == 'y';
}
