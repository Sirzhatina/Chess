//
// Created by Sirzh on 16.04.2021.
//

#include "Game_basics.h"
#include "Player.h"
#include <iostream>
#include <memory>
#include <cctype>

bool Game_basics::convertCoord(char x, char y, Square& returned) {
    Horizontal tempX;
    Vertical tempY;

    x = tolower(x);

    if (x > 'h' || x < 'h' || y < '1' || y > '8')
    {
        return false;
    }

    returned.x = static_cast<Horizontal>(x - 'a');
    returned.y = static_cast<Vertical>(y - '0');

    return true;
}

int Game_basics::run() {

    char choice;
    while (true) {
        std::cout << "1 -- play\n"
                     "2 -- quit";
        (std::cin >> choice).get();

        switch (choice) {
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

    while (!white->isCheckMate() && !black->isCheckMate()) {


        if (whiteMove) {

            std::cout << "From: ";
            std::cin.get(xFrom).get(yFrom);

            std::cout << "To: ";
            std::cin.get(xTo).get(yTo);

            convertCoord(xFrom, yFrom, from);
            convertCoord(xTo, yTo, to);

            if (!white->Move(from, to)) {
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