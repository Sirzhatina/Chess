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
    Chess::Gameplay game;
    game.addObserver(this);

    draw();
    game.start();
}

char Game_basics::getPieceKind(const Chess::Piece* p) const
{
    char result;
    if (dynamic_cast<const Chess::Pawn*>(p)) {
        result = 'p';
    } else if (dynamic_cast<const Chess::Knight*>(p)) {
        result = 'n';
    } else if (dynamic_cast<const Chess::Bishop*>(p)) {
        result = 'b';
    } else if (dynamic_cast<const Chess::Rook*>(p)) {
        result = 'r';
    } else if (dynamic_cast<const Chess::Queen*>(p)) {
        result = 'q';
    } else if (dynamic_cast<const Chess::King*>(p)) {
        result = 'k';
    }
    if (p->getColor() == Chess::Color::WHITE) {
        result = toupper(result);
    }
    return result;
}

void Game_basics::drawLine(Chess::Vertical line) const
{
    std::cout << "* " << int(line) + 1 << ' ';

    color front = cWHITE;
    color back = cBLACK;

    Chess::Coordinates coor{ Chess::Horizontal::A, line };
    for (int i = 0; i < Chess::boardSize; i++)
    {
        std::cout << '|';
        
        back = !((i + int(line)) % 2) ? cDARK_GREEN : cDARK_GRAY;
        set_color(front, back);
        std::cout << ' ';

        coor.x = Chess::Horizontal(i);
        if (Chess::Board::getInstance().getPiece(coor) != nullptr)
        {
            auto p = Chess::Board::getInstance().getPiece(coor);
            char pieceKind = getPieceKind(p);

            front = (p->getColor() == Chess::Color::WHITE) ? cWHITE : cBLACK;
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

void Game_basics::drawReversedLine(Chess::Vertical line) const
{
    std::cout << "* " << int(line) + 1 << ' ';

    color front = cWHITE;
    color back = cBLACK;

    Chess::Coordinates coor{ Chess::Horizontal::A, line };
    for (int i = Chess::boardSize - 1; i >= 0; i--)        // the only difference between this method and drawLine() is here
    {
        std::cout << '|';
        
        back = !((i + int(line)) % 2) ? cDARK_GREEN : cDARK_GRAY;
        set_color(front, back);
        std::cout << ' ';

        coor.x = Chess::Horizontal(i);
        if (Chess::Board::getInstance().getPiece(coor) != nullptr)
        {
            auto p = Chess::Board::getInstance().getPiece(coor);
            char pieceKind = getPieceKind(p);

            front = (p->getColor() == Chess::Color::WHITE) ? cWHITE : cBLACK;
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
        static constexpr auto limit = 20;
        for (counter = 0; counter < limit; counter++) std::cout << "* ";
        std::cout << '\t';
        for (counter = 0; counter < limit; counter++) std::cout << "* ";
    };

    drawBorder();
    set_cursor_pos(indentX, ++line);

    for (int i = Chess::boardSize - 1, j = 0; i >= 0 && j < Chess::boardSize; i--, j++)
    {
        drawLine(Chess::Vertical{i});
        std::cout << '\t';
        drawReversedLine(Chess::Vertical{j});
        set_cursor_pos(indentX, ++line);
    }

    std::cout << "*   ";
    for (char i = 'a'; i - 'a' < Chess::boardSize; i++)
    {
        std::cout << "  " << i << ' ';
    }
    std::cout << "  *\t";

    std::cout << "*   ";
    for (char i = 'a' + Chess::boardSize - 1; i >= 'a'; i--)
    {
        std::cout << "  " << i << ' ';
    }
    std::cout << "  *";
    set_cursor_pos(indentX, ++line);

    drawBorder();
    set_cursor_pos(indentX, ++line);
}

void Game_basics::handleEvent(const Chess::Gameplay* observed)
{
    system("cls");
    draw();
}