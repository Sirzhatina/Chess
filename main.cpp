#include "Game_basics.hpp"
#include <iostream>
int main()
{
    Game_basics launcher;
    try
    {
        return launcher.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}
