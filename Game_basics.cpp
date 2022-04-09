//
// Created by Sirzh on 16.04.2021.
//

#include "Game_basics.hpp"
#include <Core/Player.hpp>
#include <Core/Board.hpp>
#include <Core/Primitives.hpp>
#include <regex>
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

Chess::Move Game_basics::getMove() const
{
    std::string coord;
    std::regex pattern(R"([a-h][1-8] [a-h][1-8])");

    std::cout << "Move: ";
    std::getline(std::cin, coord);
    
    if (!std::regex_match(coord, pattern))
    {
        throw std::runtime_error{ "Invalid input!" };
    }

    auto convertCoord = [this](int x, int y) -> Chess::Coordinates
    {
        return { Chess::Horizontal{ x }, Chess::Vertical{ y } };
    };


    try
    {
        Chess::Move result
        { 
            convertCoord(coord[0] - 'a', coord[1] - '1'), 
            convertCoord(coord[3] - 'a', coord[4] - '1') 
        };
        return result;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(EXIT_FAILURE);
    }
}

void Game_basics::play()
{
    _gameplay.start();
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
    if (p->player()->color() == Chess::Color::WHITE) {
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
        if (_gameplay.board()->getPiece(coor) != nullptr)
        {
            auto p = _gameplay.board()->getPiece(coor);
            char pieceKind = getPieceKind(p);

            front = (p->player()->color() == Chess::Color::WHITE) ? cWHITE : cBLACK;
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
        if (_gameplay.board()->getPiece(coor) != nullptr)
        {
            auto p = _gameplay.board()->getPiece(coor);
            char pieceKind = getPieceKind(p);

            front = (p->player()->color() == Chess::Color::WHITE) ? cWHITE : cBLACK;
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

void Game_basics::drawBoard(const Chess::Board* board)
{
    int line = 5;
    constexpr auto indentX = 10;
    set_cursor_pos(indentX, line);

    auto drawBorder = []()
    {
        short counter = 0;
        static constexpr auto limit = 20;
        for (; counter < limit; counter++) std::cout << "* ";
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
