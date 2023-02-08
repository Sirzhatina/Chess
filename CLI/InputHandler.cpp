#include "InputHandler.hpp"

#include <iostream>
#include <string>


std::future<Chess::Move> InputHandler::getMove()
{
    auto makeMove = [this]() -> Chess::Move
    {
        m_moveRetrieved.store(false);

        std::string inputField;
        std::optional<Chess::Coordinates> from, to;

        do {
            std::cout << "Move: ";
            std::getline(std::cin, inputField);
    
            from = Chess::Coordinates::makeCoord(inputField[0] - 'a', inputField[1] - '1');
            to   = Chess::Coordinates::makeCoord(inputField[3] - 'a', inputField[4] - '1');

            if (inputField == quitCommand && wantToQuit())
            {
                throw ExitCase{"Do svidanya, spasibo, prihodite eshche"};
            }
        } while (!from || !to);

        m_moveRetrieved.store(true);

        return {*from, *to};
    };

    return std::async(std::launch::async, std::move(makeMove));
}

bool InputHandler::wantToQuit() const 
{
    std::cout << "Are you sure you want to quit the match? y/n: ";
    char choice = std::cin.get();

    while (std::cin.get() != '\n');

    return choice == 'y';
}
