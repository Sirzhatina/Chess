//
// Created by Sirzh on 16.04.2021.
//

#include "Game_basics.h"
#include "Player.h"
#include <iostream>
#include <memory>

bool Game_basics::convertCoord(char x, char y, Coordinates& returned) {
    Horizontal tempX;
    Vertical tempY;

    switch (x) {
        case 'a':
        case 'A': tempX = Horizontal::A;
            break;
        case 'b':
        case 'B': tempX = Horizontal::B;
            break;
        case 'c':
        case 'C': tempX = Horizontal::C;
            break;
        case 'd':
        case 'D': tempX = Horizontal::D;
            break;
        case 'e':
        case 'E': tempX = Horizontal::E;
            break;
        case 'f':
        case 'F': tempX = Horizontal::F;
            break;
        case 'g':
        case 'G': tempX = Horizontal::G;
            break;
        case 'h':
        case 'H': tempX = Horizontal::H;
            break;
        default:
            return false;
    }
    switch (y) {
        case '1': tempY = Vertical::one;
            break;
        case '2': tempY = Vertical::two;
            break;
        case '3': tempY = Vertical::three;
            break;
        case '4': tempY = Vertical::four;
            break;
        case '5': tempY = Vertical::five;
            break;
        case '6': tempY = Vertical::six;
            break;
        case '7': tempY = Vertical::seven;
            break;
        case '8': tempY = Vertical::eight;
            break;
        default:
            return false;
    }

    returned.x = tempX;
    returned.y = tempY;

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

    Coordinates from, to;

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