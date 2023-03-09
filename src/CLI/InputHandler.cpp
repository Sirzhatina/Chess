#include "InputHandler.hpp"

#include <iostream>
#include <string>
#include <optional>
#include <Core/Primitives.hpp>
#include "CLI.hpp"

IInputHandler::MoveResult InputHandler::getMove()
{
    auto makeMove = [this]() -> std::variant<Chess::Move, QuitToken>
    {
        std::string inputField;
        std::optional<Chess::Coordinates> from, to;

        while (!from || !to)
        {
            std::cout << CLI::tab << "Move: ";
            std::getline(std::cin, inputField);

            if (inputField == quitCommand && wantToQuit())
            {
                return QuitToken{};
            }
            if (inputField.size() != 5) continue; // 5 is the size of a string with correct move
            
            from = Chess::Coordinates::makeCoord(inputField[0] - 'a', inputField[1] - '1');
            to   = Chess::Coordinates::makeCoord(inputField[3] - 'a', inputField[4] - '1');
        }

        return Chess::Move{*from, *to};
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
