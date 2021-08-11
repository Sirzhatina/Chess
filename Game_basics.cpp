//
// Created by Sirzh on 16.04.2021.
//

#include "Game_basics.h"
#include "Player.h"
#include "Board.h"
#include "Traits.h"
#include <iostream>


int Game_basics::run()
{
    char choice;
    while (true)
    {
        system("cls");

        std::cout << "1 -- play\n"
                     "2 -- quit";
        (std::cin >> choice).get();

        switch (choice)
        {
            case '1': play();
                break;
            case '2':
                system("pause");
                return 0;
            default:
                continue;
        }

    }
}

void Game_basics::play()
{

    while (!white->isCheckmate() && !black->isCheckmate())
    {
        std::cout << "From: ";
        std::cin.get(xFrom).get(yFrom);

        std::cout << "To: ";
        std::cin.get(xTo).get(yTo);

        if (!from.setCoord(xFrom, yFrom) || !to.setCoord(xTo, yTo))
        {
            continue;
        }

        if (whiteMove)
        {
            if (!white->Move(from, to))
            {
                std::cout << "Wrong move\n";
                continue;
            }
        }
        else {

        }
        whiteMove = !whiteMove;
    }

    std::cout << (white->isCheckMate() ? "\nBlack win" : "\nWhite win") << std::endl;
}