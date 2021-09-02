//
// Created by Sirzh on 16.04.2021.
//

#include "Game_basics.h"
#include "Player.h"
#include "Board.h"
#include "Traits.h"
#include <typeinfo>
#include <iostream>


int Game_basics::run()
{
    char choice;
    while (true)
    {
        system("cls");

        std::cout << "1 -- play\n"
                     "2 -- quit\n";
        (std::cin >> choice).get();

        switch (choice)
        {
            case '1':
                system("cls"); 
                play();
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
    draw();
}

void Game_basics::draw()
{
    char piece;
    auto definePiece = [&piece](const Piece* p)
    {
        if (typeid(p) == typeid(Pawn))
        {
            piece = 'p';
        }
        else if (typeid(p) == typeid(Knight))
        {
            piece = 'n';
        }
        else if (typeid(p) == typeid(Bishop))
        {
            piece = 'b';
        }
        else if (typeid(p) == typeid(Rook))
        {
            piece = 'r';
        }
        else if (typeid(p) == typeid(Queen))
        {
            piece = 'q';
        }
        else if (typeid(p) == typeid(King))
        {
            piece = 'k';
        }
        if (p->getColor() == Traits::Color::WHITE)
        {
            piece = toupper(piece);
        }
    };
    auto print = [=]() 
    {
        for (int i = 0; i < 20; i++) std::cout << "* ";
        std::cout << std::endl;
    };

    print();
    char colorSign; // ' ' for white squares and '_' for black ones
    Traits::Coordinates coor;
    for (int i = 0; i < Traits::boardSize; i++)
    {
        std::cout << "* " << Traits::boardSize - i << ' ';
        for (int j = 0; j < Traits::boardSize; j++)
        {
            colorSign = ((i + j) % 2) ? '_' : 'F';
            coor.x = Traits::Horizontal{j};
            coor.y = Traits::Vertical{ Traits::boardSize - i - 1 };
            
            definePiece(game.getBoard()->getPiece(coor));
            std::cout << '|' << colorSign << piece << colorSign;
        }
        std::cout << "| *" << std::endl;
    }

    std::cout << "*   ";
    for (char i = 'a'; i - 'a' < Traits::boardSize; i++)
    {
        std::cout << ' ' << i;
    }
    std::cout << "   *" << std::endl;
    print();

}

void Game_basics::handleEvent(const Gameplay* observed)
{
    draw();
}