#include "Drawer.hpp"
#include <cstdlib>

void Drawer::drawMainMenu() const
{
    system(clear);

    // 10 positions down from left up corner
    std::cout << "\n\n\n\n\n\n\n\n\n\n";
    // 30 positions right from left border on the line
    auto tab = [] { std::cout << "                              "; };

    tab(); std::cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
    tab(); std::cout << "*           WELCOME TO THE BEST GAME YOU'VE EVER            *\n";
    tab(); std::cout << "*                        EXPERIENCED                        *\n";
    tab(); std::cout << "*                                                           *\n";
    tab(); std::cout << "*                  Choose the option below                  *\n";
    tab(); std::cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
    std::cout << "\n\n";
    tab(); std::cout << "1 - Play.\n";
    tab(); std::cout << "2 - Settings (not implemented).\n";
    tab(); std::cout << "3 - Quit.\n";
    tab(); std::cout << "Input: ";
}

// void Drawer::drawPlay() const
// {
// /*
//  *    * * * * * * * * * * * * * * * * * * * *   * * * * * * * * * * * * * * * * * * * *
//  *    * 8 | r |_b_| n |_q_| k |_n_| b |_r_| *   * 1 | R |_B_| N |_K_| Q |_N_| B |_R_| *   
//  *    * 7 |_p_| p |_p_| p |_p_| p |_p_| p | *   * 2 |_P_| P |_P_| P |_P_| P |_P_| P | *
//  *    * 6 |   |_ _|   |_ _|   |_ _|   |_ _| *   * 3 |   |_ _|   |_ _|   |_ _|   |_ _| *
//  *    * 5 |_ _|   |_ _|   |_ _|   |_ _|   | *   * 4 |_ _|   |_ _|   |_ _|   |_ _|   | *
//  *    * 4 |   |_ _|   |_ _|   |_ _|   |_ _| *   * 5 |   |_ _|   |_ _|   |_ _|   |_ _| *
//  *    * 3 |_ _|   |_ _|   |_ _|   |_ _|   | *   * 6 |_ _|   |_ _|   |_ _|   |_ _|   | *
//  *    * 2 | P |_P_| P |_P_| P |_P_| P |_P_| *   * 7 | p |_p_| p |_p_| p |_p_| p |_p_| *
//  *    * 1 |_R_| B |_N_| Q |_K_| N |_B_| R | *   * 8 |_r_| b |_n_| k |_q_| n |_b_| r | *
//  *    *     a   b   c   d   e   f   g   h   *   *     h   g   f   e   d   c   b   a   *
//  *    * * * * * * * * * * * * * * * * * * * *   * * * * * * * * * * * * * * * * * * * *
//  * */


// }