#include "CLI.hpp"
#include "BoardDrawer.hpp"
#include <Core/Player.hpp>

void BoardDrawer::drawBoard(std::shared_ptr<const Chess::Board> b) const
{
    system(CLI::clear);

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


    std::cout << "\n\n\n\n\n\n\n\n\n\n";
    CLI::tab(); std::cout << "* * * * * * * * * * * * * * * * * * * *\t\t* * * * * * * * * * * * * * * * * * * *\n";

    using std::cout;
    using namespace Chess;
    for (int i = Chess::boardSize - 1; i >= 0; i--)
    {
        // how one line looks
        CLI::tab(); drawLine(Vertical(i)); cout << "\t\t"; drawLine(Vertical(boardSize - 1 - i), true); cout << '\n';
    }
    CLI::tab(); std::cout << "*     a   b   c   d   e   f   g   h   *\t\t*     h   g   f   e   d   c   b   a   *\n";

    CLI::tab(); std::cout << "* * * * * * * * * * * * * * * * * * * *\t\t* * * * * * * * * * * * * * * * * * * *\n";
}

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