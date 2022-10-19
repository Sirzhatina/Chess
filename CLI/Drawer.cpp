#include "Drawer.hpp"
#include <cstdlib>
#include "InputHandler.hpp"
#include <Core/Player.hpp>

void Drawer::drawMainMenu() const
{
    system(clear);

    // 10 positions down from left up corner
    std::cout << "\n\n\n\n\n\n\n\n\n\n";

    tab(); std::cout << "\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
    tab(); std::cout << "\t\t*           WELCOME TO THE BEST GAME YOU'VE EVER            *\n";
    tab(); std::cout << "\t\t*                        EXPERIENCED                        *\n";
    tab(); std::cout << "\t\t*                                                           *\n";
    tab(); std::cout << "\t\t*                  Choose the option below                  *\n";
    tab(); std::cout << "\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
    std::cout << "\n\n";
    tab(); std::cout << "1 - Play.\n";
    tab(); std::cout << "2 - Settings (not implemented).\n";
    tab(); std::cout << "3 - Quit.\n";
    tab(); std::cout << "Input: ";
}

void Drawer::drawBoard(std::shared_ptr<const Chess::Board> b) const
{
    system(clear);

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
        if (p->player()->color() == Chess::Color::WHITE) {
            result = std::toupper(result);
        }
        return result;
    };
    
    auto drawSquare = [](bool whiteSquare, char piece = ' ')
    {
        // draws '_P_|' or ' P |'
        char space = whiteSquare ? ' ' : '_';
        std::cout << space << piece << space << '|';
    };

/*
 *    * * * * * * * * * * * * * * * * * * * *   * * * * * * * * * * * * * * * * * * * *
 *    * 8 | r |_b_| n |_q_| k |_n_| b |_r_| *   * 1 | R |_B_| N |_K_| Q |_N_| B |_R_| *
 *    * 7 |_p_| p |_p_| p |_p_| p |_p_| p | *   * 2 |_P_| P |_P_| P |_P_|   |_P_| P | *
 *    * 6 |   |_ _|   |_ _|   |_ _|   |_ _| *   * 3 |   |_ _|   |_ _|   |_ _|   |_ _| *
 *    * 5 |_ _|   |_ _|   |_ _|   |_ _|   | *   * 4 |_ _|   |_ _|   |_ _| P |_ _|   | *
 *    * 4 |   |_ _| P |_ _|   |_ _|   |_ _| *   * 5 |   |_ _|   |_ _|   |_ _|   |_ _| *
 *    * 3 |_ _|   |_ _|   |_ _|   |_ _|   | *   * 6 |_ _|   |_ _|   |_ _|   |_ _|   | *
 *    * 2 | P |_P_|   |_P_| P |_P_| P |_P_| *   * 7 | p |_p_| p |_p_| p |_p_| p |_p_| *
 *    * 1 |_R_| B |_N_| Q |_K_| N |_B_| R | *   * 8 |_r_| b |_n_| k |_q_| n |_b_| r | *
 *    *     a   b   c   d   e   f   g   h   *   *     h   g   f   e   d   c   b   a   *
 *    * * * * * * * * * * * * * * * * * * * *   * * * * * * * * * * * * * * * * * * * *
 */


    auto drawLine = [&](Chess::Vertical l, bool reversed = false)
    {
        std::cout << "* " << int(l) + 1 << " |";
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
        std::cout << " *";
    };



    tab(); std::cout << "* * * * * * * * * * * * * * * * * * * *\t* * * * * * * * * * * * * * * * * * * *\n";

    for (int i = Chess::boardSize - 1; i >= 0; i--)
    {
        tab(); drawLine(Chess::Vertical(i)); 
        std::cout << '\t'; 
        drawLine(Chess::Vertical(Chess::boardSize - 1 - i), true); std::cout << '\n';
    }

    tab(); std::cout << "* * * * * * * * * * * * * * * * * * * *\t* * * * * * * * * * * * * * * * * * * *\n";

}