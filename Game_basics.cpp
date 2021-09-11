//
// Created by Sirzh on 16.04.2021.
//

#include "Game_basics.h"
#include "Player.h"
#include "Board.h"
#include "Traits.h"
#include "Msoftcon.h"
#include <typeinfo>
#include <iostream>

Game_basics::Game_basics()
{
    game.addObserver(this);
    init_graphics();
}

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
    game.start();
}

char Game_basics::getPieceKind(const Piece* p) const
{
    char result;
    if (dynamic_cast<const Pawn*>(p)) {
        result = 'p';
    } else if (dynamic_cast<const Knight*>(p)) {
        result = 'n';
    } else if (dynamic_cast<const Bishop*>(p)) {
        result = 'b';
    } else if (dynamic_cast<const Rook*>(p)) {
        result = 'r';
    } else if (dynamic_cast<const Queen*>(p)) {
        result = 'q';
    } else if (dynamic_cast<const King*>(p)) {
        result = 'k';
    }
    if (p->getColor() == Traits::Color::WHITE) {
        result = toupper(result);
    }
    return result;
}

void Game_basics::drawLine(Traits::Vertical line) const
{
    std::cout << "* " << int(line) + 1 << ' ';

    color front = cWHITE;
    color back = cBLACK;

    Traits::Coordinates coor{ Traits::Horizontal::A, line };
    for (int i = 0; i < Traits::boardSize; i++)
    {
        std::cout << '|';
        
        back = !((i + int(line)) % 2) ? cDARK_GREEN : cDARK_GRAY;
        set_color(front, back);
        std::cout << ' ';

        coor.x = Traits::Horizontal(i);
        if (Board::getInstance().getPiece(coor) != nullptr)
        {
            auto p = Board::getInstance().getPiece(coor);
            char pieceKind = getPieceKind(p);

            front = (p->getColor() == Traits::Color::WHITE) ? cWHITE : cBLACK;
            set_color(front, back);
            std::cout << pieceKind;
        }
        else
        {
            std::cout << ' ';
        }
        std::cout << ' ';
        set_color(cWHITE, cBLACK);
    }
    std::cout << "| *";
}

void Game_basics::drawReversedLine(Traits::Vertical line) const
{
    std::cout << "* " << int(line) + 1 << ' ';

    color front = cWHITE;
    color back = cBLACK;

    Traits::Coordinates coor{ Traits::Horizontal::A, line };
    for (int i = Traits::boardSize - 1; i >= 0; i--)        // the only difference between this method and drawLine() is here
    {
        std::cout << '|';
        
        back = !((i + int(line)) % 2) ? cDARK_GREEN : cDARK_GRAY;
        set_color(front, back);
        std::cout << ' ';

        coor.x = Traits::Horizontal(i);
        if (Board::getInstance().getPiece(coor) != nullptr)
        {
            auto p = Board::getInstance().getPiece(coor);
            char pieceKind = getPieceKind(p);

            front = (p->getColor() == Traits::Color::WHITE) ? cWHITE : cBLACK;
            set_color(front, back);
            std::cout << pieceKind;
        }
        else
        {
            std::cout << ' ';
        }
        std::cout << ' ';
        set_color(cWHITE, cBLACK);
    }
    std::cout << "| *";
}

void Game_basics::draw() const
{
    int line = 5;
    constexpr auto indentX = 10;
    set_cursor_pos(indentX, line);

    auto drawBorder = []()
    {
        short counter;
        for (counter = 0; counter < 20; counter++) std::cout << "* ";
        std::cout << '\t';
        for (counter = 0; counter < 20; counter++) std::cout << "* ";
    };

    drawBorder();
    set_cursor_pos(indentX, ++line);

    for (int i = Traits::boardSize - 1, j = 0; i >= 0 && j < Traits::boardSize; i--, j++)
    {
        drawLine(Traits::Vertical{i});
        std::cout << '\t';
        drawReversedLine(Traits::Vertical{j});
        set_cursor_pos(indentX, ++line);
    }

    std::cout << "*   ";
    for (char i = 'a'; i - 'a' < Traits::boardSize; i++)
    {
        std::cout << "  " << i << ' ';
    }
    std::cout << "  *\t";

    std::cout << "*   ";
    for (char i = 'a' + Traits::boardSize - 1; i >= 'a'; i--)
    {
        std::cout << "  " << i << ' ';
    }
    std::cout << "  *";
    set_cursor_pos(indentX, ++line);

    drawBorder();
    set_cursor_pos(indentX, ++line);
}

void Game_basics::handleEvent(const Gameplay* observed)
{
    system("cls");
    draw();
}