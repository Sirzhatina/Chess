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

Game_basics::Game_basics(std::ostream& drawOutput, std::istream& askInput)
: _gameplay(this)
, _drawOutput{drawOutput}
, _askInput{askInput} { init_graphics(); }

int Game_basics::run()
{
    char choice;
    while (true)
    {
        system("cls");

        _drawOutput << "1 -- play\n"
                     "2 -- quit\n";
        (_askInput >> choice).get();

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

    _drawOutput << "Move: ";
    std::getline(_askInput, coord);
    
    if (!std::regex_match(coord, pattern))
    {
        throw std::runtime_error{ "Invalid input!" };
    }

    try
    {
        Chess::Move result{ {coord[0] - 'a', coord[1] - '1'}, {coord[3] - 'a', coord[4] - '1'} };
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
    _drawOutput << "* " << int(line) + 1 << ' ';

    color front = cWHITE;
    color back = cBLACK;

    Chess::Coordinates coor{ Chess::Horizontal::A, line };
    for (int i = 0; i < Chess::boardSize; i++)
    {
        _drawOutput << '|';
        
        back = !((i + int(line)) % 2) ? cDARK_GREEN : cDARK_GRAY;
        set_color(front, back);
        _drawOutput << ' ';

        coor.x = Chess::Horizontal(i);
        if (_gameplay.board()->getPiece(coor) != nullptr)
        {
            auto p = _gameplay.board()->getPiece(coor);
            char pieceKind = getPieceKind(p);

            front = (p->player()->color() == Chess::Color::WHITE) ? cWHITE : cBLACK;
            set_color(front, back);
            _drawOutput << pieceKind;
        }
        else
        {
            _drawOutput << ' ';
        }
        _drawOutput << ' ';
        set_color(cWHITE, cBLACK);
    }
    _drawOutput << "| *";
}

void Game_basics::drawReversedLine(Chess::Vertical line) const
{
    _drawOutput << "* " << int(line) + 1 << ' ';

    color front = cWHITE;
    color back = cBLACK;

    Chess::Coordinates coor{ Chess::Horizontal::A, line };
    for (int i = Chess::boardSize - 1; i >= 0; i--)        // the only difference between this method and drawLine() is here
    {
        _drawOutput << '|';
        
        back = !((i + int(line)) % 2) ? cDARK_GREEN : cDARK_GRAY;
        set_color(front, back);
        _drawOutput << ' ';

        coor.x = Chess::Horizontal(i);
        if (_gameplay.board()->getPiece(coor) != nullptr)
        {
            auto p = _gameplay.board()->getPiece(coor);
            char pieceKind = getPieceKind(p);

            front = (p->player()->color() == Chess::Color::WHITE) ? cWHITE : cBLACK;
            set_color(front, back);
            _drawOutput << pieceKind;
        }
        else
        {
            _drawOutput << ' ';
        }
        _drawOutput << ' ';
        set_color(cWHITE, cBLACK);
    }
    _drawOutput << "| *";
}

void Game_basics::drawBoard(const Chess::Board* board)
{
    int line = 5;
    constexpr auto indentX = 10;
    set_cursor_pos(indentX, line);

    auto drawBorder = [this]()
    {
        short counter = 0;
        static constexpr auto limit = 20;
        for (; counter < limit; counter++) _drawOutput << "* ";
        _drawOutput << '\t';
        for (; counter > 0; counter--) _drawOutput << "* ";
    };

    drawBorder();
    set_cursor_pos(indentX, ++line);

    for (int i = Chess::boardSize - 1, j = 0; i >= 0 && j < Chess::boardSize; i--, j++)
    {
        drawLine(Chess::Vertical{i});
        _drawOutput << '\t';
        drawReversedLine(Chess::Vertical{j});
        set_cursor_pos(indentX, ++line);
    }

    _drawOutput << "*   ";
    for (char i = 'a'; i - 'a' < Chess::boardSize; i++)
    {
        _drawOutput << "  " << i << ' ';
    }
    _drawOutput << "  *\t";

    _drawOutput << "*   ";
    for (char i = 'a' + Chess::boardSize - 1; i >= 'a'; i--)
    {
        _drawOutput << "  " << i << ' ';
    }
    _drawOutput << "  *";
    set_cursor_pos(indentX, ++line);

    drawBorder();
    set_cursor_pos(indentX, ++line);
}
