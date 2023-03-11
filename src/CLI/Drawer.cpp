#include <iostream>
#include "CLI.hpp"
#include "Drawer.hpp"
#include <Core/Player.hpp>
#include <Core/Settings.hpp>
#include <Core/Match.hpp>

void Drawer::drawMainMenu() const
{
    CLI::clear();
    using std::cout;

    cout << CLI::down;

    cout 
        << CLI::dTab << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n"
        << CLI::dTab << "*           WELCOME TO THE BEST GAME YOU'VE EVER            *\n"
        << CLI::dTab << "*                        EXPERIENCED                        *\n"
        << CLI::dTab << "*                                                           *\n"
        << CLI::dTab << "*                  Choose the option below                  *\n"
        << CLI::dTab << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n"
        << "\n\n"

        << CLI::dTab << "1 - Play.\n"
        << CLI::dTab << "2 - Settings.\n"
        << CLI::dTab << "q - Quit.\n"
        << CLI::dTab << "Input: ";
}

void Drawer::drawSettingsMenu() const
{
    CLI::clear();
    std::cout
        << CLI::down
        << CLI::dTab << "[SETTINGS]\n"
        << CLI::dTab << "1 - Match\n"
        << CLI::dTab << "q - Back to main menu\n"
        << CLI::dTab << "Input: ";
}

void Drawer::drawPlay(const Chess::Match& match) const
{
    CLI::clear();
    std::cout << CLI::down;

    if (Settings::instance().m_mSettings.tm != Settings::Match::Time::no_time)
    {
        showRemainingTime(match);
    }
    drawBoard(match.board());
}

void Drawer::showRemainingTime(const Chess::Match& match) const
{
    auto tm = [](const Chess::Match& match, Chess::Color c)
    {
        return  std::to_string(std::uint64_t(std::ceil(match.remainingTime(c).count()) / 60)) + ':' + 
                std::to_string(std::uint64_t(std::ceil(match.remainingTime(c).count())) % 60);
    };

    std::cout << CLI::tab << std::setw(5) << tm(match, Chess::Color::WHITE);
    std::cout << "                                             ";
    std::cout << std::setw(5) << tm(match, Chess::Color::BLACK) << '\n';

}

void Drawer::drawBoard(const Chess::Board& b) const
{
    using std::cout;

    auto getPieceKind = [](const Chess::Piece* p)
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
        else {
            return ' ';
        }
        return p->player()->color() == Chess::Color::WHITE ? char(std::toupper(result)) : result;
    };
    
    auto drawSquare = [](bool whiteSquare, char piece = ' ')
    {
        // draws '_P_|' or ' P |'
        char space = whiteSquare ? ' ' : '_';
        cout << space << piece << space << '|';
    };

    auto drawLine = [&](Chess::Vertical l, bool reversed = false)
    {
        cout << "* " << int(l) + 1 << " |";
        if (!reversed)
        {
            for (int i = 0; i < Chess::boardSize; i++)
            {
                drawSquare((int(l) + i) % 2, getPieceKind(b.getPiece({i, int(l)})));
            }
        }
        else
        {
            for (int i = Chess::boardSize - 1; i >= 0; i--)
            {
                drawSquare((int(l) + i) % 2, getPieceKind(b.getPiece({i, int(l)})));
            }
        }
        cout << " *";
    };

    cout << CLI::tab << "* * * * * * * * * * * * * * * * * * * *\t\t* * * * * * * * * * * * * * * * * * * *\n";

    using namespace Chess;
    for (int i = Chess::boardSize - 1; i >= 0; i--)
    {
        // how one line looks
        cout << CLI::tab; drawLine(Vertical(i)); 
        cout << CLI::tab; drawLine(Vertical(boardSize - 1 - i), true); 
        cout << '\n';
    }
    cout << CLI::tab << "*     a   b   c   d   e   f   g   h   *\t\t*     h   g   f   e   d   c   b   a   *\n"
         << CLI::tab << "* * * * * * * * * * * * * * * * * * * *\t\t* * * * * * * * * * * * * * * * * * * *\n";
}

void Drawer::drawMatchEnd(Chess::Match::Winner w) const
{
    using enum Chess::Match::Winner;

    std::cout << "\n\n" << CLI::dTab
              << (w == stalemate ? "Stalemate.\n" : (w == white ? "White" : "Black") + std::string(" won. "))
              << "Dosvidanya, spasibo, prihodite esh4e."
              << std::endl;
    std::cin.get();
}