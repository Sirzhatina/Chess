//
// Created by Sirzh on 16.04.2021.
//

#include "Game_basics.h"
#include "Player.h"
#include "Square.h"
#include <iostream>
#include <memory>

int Game_basics::run()
{
    system("cls");

    char choice;
    while (true) {
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

void Game_basics::play() {

    std::unique_ptr<Player> white = std::make_unique<Player>(Player::color::WHITE);
    std::unique_ptr<Player> black = std::make_unique<Player>(Player::color::BLACK);

    bool whiteMove = true;

    char xFrom, yFrom;
    char xTo, yTo;

    Square from, to;

    while (!white->isCheckMate() && !black->isCheckMate())
    {
        std::cout << "From: ";
        std::cin.get(xFrom).get(yFrom);

        std::cout << "To: ";
        std::cin.get(xTo).get(yTo);

        Square::convertCoord(xFrom, yFrom, from);
        Square::convertCoord(xTo, yTo, to);

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