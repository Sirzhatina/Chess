#include "Game_basics.hpp"
#include <iostream>
#include "CLI/Launcher.hpp"
#include "CLI/GameplayHandler.hpp"
#include "CLI/Drawer.hpp"
int main()
{
    auto code = Launcher<Drawer, GameplayHandler>().launch();

    if (code)
    {
        std::cerr << "Something went wrong\n";
        return int(code);
    }
    return 0;
    // Game_basics launcher;
    // try
    // {
    //     return launcher.run();
    // }
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << '\n';
    // }
}
