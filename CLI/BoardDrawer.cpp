#include <iostream>
#include "CLI.hpp"
#include "BoardDrawer.hpp"
#include <Core/Player.hpp>
#include <Core/Settings.hpp>

void BoardDrawer::drawBoard(std::shared_ptr<const Chess::Board> b) const
{
    system(CLI::clear);
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
                drawSquare((int(l) + i) % 2, getPieceKind(b->getPiece({i, int(l)})));
            }
        }
        else
        {
            for (int i = Chess::boardSize - 1; i >= 0; i--)
            {
                drawSquare((int(l) + i) % 2, getPieceKind(b->getPiece({i, int(l)})));
            }
        }
        cout << " *";
    };

    cout << CLI::down
         << CLI::tab 
         << "* * * * * * * * * * * * * * * * * * * *\t\t* * * * * * * * * * * * * * * * * * * *\n";

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

/*
 *    * * * * * * * * * * * * * * * * * * * *   * * * * * * * * * * * * * * * * * * * *
 *    * 8 | r |_n_| b |_q_| k |_b_| n |_r_| *   * 1 | R |_N_| B |_K_| Q |_B_| N |_R_| *
 *    * 7 |_p_| p |_p_| p |_p_| p |_p_| p | *   * 2 |_P_| P |_P_| P |_P_|   |_P_| P | *
 *    * 6 |   |_ _|   |_ _|   |_ _|   |_ _| *   * 3 |   |_ _|   |_ _|   |_ _|   |_ _| *
 *    * 5 |_ _|   |_ _|   |_ _|   |_ _|   | *   * 4 |_ _|   |_ _|   |_ _| P |_ _|   | *
 *    * 4 |   |_ _| P |_ _|   |_ _|   |_ _| *   * 5 |   |_ _|   |_ _|   |_ _|   |_ _| *
 *    * 3 |_ _|   |_ _|   |_ _|   |_ _|   | *   * 6 |_ _|   |_ _|   |_ _|   |_ _|   | *
 *    * 2 | P |_P_|   |_P_| P |_P_| P |_P_| *   * 7 | p |_p_| p |_p_| p |_p_| p |_p_| *
 *    * 1 |_R_| N |_B_| Q |_K_| B |_N_| R | *   * 8 |_r_| n |_b_| k |_q_| b |_n_| r | *
 *    *     a   b   c   d   e   f   g   h   *   *     h   g   f   e   d   c   b   a   *
 *    * * * * * * * * * * * * * * * * * * * *   * * * * * * * * * * * * * * * * * * * *
 */