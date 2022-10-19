#include "InputHandler.hpp"

#include <iostream>
#include <string>


Chess::Move InputHandler::getMove() const
{
    std::string coord;

    std::cout << "Move: ";
    std::getline(std::cin, coord);
    
    if (coord == quitCommand && wantToQuit())
    {
        throw ExitCase{"Do svidanya, spasibo, prihodite eshche"};
    }

    Chess::Move result{ {coord[0] - 'a', coord[1] - '1'}, {coord[3] - 'a', coord[4] - '1'} };
    return result;
}

bool InputHandler::wantToQuit() const 
{
    std::cout << "Are you sure you want to quit the match? y/n: ";
    char choice = std::cin.get();

    while (std::cin.get() != '\n');

    return choice == 'y';
}

// void GameplayHandler::drawBoard(std::shared_ptr<const Chess::Board> b) const
// {
// /*
//  *    * * * * * * * * * * * * * * * * * * * *   * * * * * * * * * * * * * * * * * * * *
//  *    * 8 | r |_b_| n |_q_| k |_n_| b |_r_| *   * 1 | R |_B_| N |_K_| Q |_N_| B |_R_| *
//  *    * 7 |_p_| p |_p_| p |_p_| p |_p_| p | *   * 2 |_P_| P |_P_| P |_P_|   |_P_| P | *
//  *    * 6 |   |_ _|   |_ _|   |_ _|   |_ _| *   * 3 |   |_ _|   |_ _|   |_ _|   |_ _| *
//  *    * 5 |_ _|   |_ _|   |_ _|   |_ _|   | *   * 4 |_ _|   |_ _|   |_ _| P |_ _|   | *
//  *    * 4 |   |_ _| P |_ _|   |_ _|   |_ _| *   * 5 |   |_ _|   |_ _|   |_ _|   |_ _| *
//  *    * 3 |_ _|   |_ _|   |_ _|   |_ _|   | *   * 6 |_ _|   |_ _|   |_ _|   |_ _|   | *
//  *    * 2 | P |_P_|   |_P_| P |_P_| P |_P_| *   * 7 | p |_p_| p |_p_| p |_p_| p |_p_| *
//  *    * 1 |_R_| B |_N_| Q |_K_| N |_B_| R | *   * 8 |_r_| b |_n_| k |_q_| n |_b_| r | *
//  *    *     a   b   c   d   e   f   g   h   *   *     h   g   f   e   d   c   b   a   *
//  *    * * * * * * * * * * * * * * * * * * * *   * * * * * * * * * * * * * * * * * * * *
//  * */

//     auto drawSquare = [](bool whiteSquare, char piece = ' ')
//     {
//         char kek = whiteSquare ? '_' : ' ';
//         std::cout << kek << piece << kek << '|';
//     };

//     auto drawLine = [](Chess::Vertical l, bool reversed = false)
//     {
//         std::cout << "* " << int(l) + 1 << " |";

//         for (int i = 0; i < Chess::boardSize; i++)
//         {

//         }
//     };

//     tab(); std::cout << "* * * * * * * * * * * * * * * * * * * *  \t* * * * * * * * * * * * * * * * * * * *\n";


//     tab(); std::cout << "* * * * * * * * * * * * * * * * * * * *  \t* * * * * * * * * * * * * * * * * * * *\n";

// }