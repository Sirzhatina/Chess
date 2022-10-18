#include "GameplayHandler.hpp"

#include <iostream>
#include <string>

 
// int GameplayHandler::run()
// {
//     char choice;
//     while (true)
//     {
//         dr->drawMainMenu();
//         (std::cin >> choice).get();

//         switch (choice)
//         {
//         case '1':
//             play();
//             break;
//         case '2':
//             dr->drawSettingsMenu();
//             break;
//         case '3':
//             system("pause");
//             return 0;
//         default:
//             continue;
//         }
//     }
// }

Chess::Move GameplayHandler::getMove() const
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

bool GameplayHandler::wantToQuit() const 
{
    std::cout << "Are you sure you want to quit the match? y/n: ";
    char choice = std::cin.get();

    while (std::cin.get() != '\n');

    return choice == 'y';
}

void GameplayHandler::drawBoard(const Chess::Board* b)
{
    
}