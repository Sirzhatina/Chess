#include "Game_basics.hpp"
#include <iostream>
#include "CLI/Launcher.hpp"
#include "CLI/GameplayHandler.hpp"
#include "CLI/Drawer.hpp"
#include "CLI/ILauncher.hpp"

int main()
{
    
    std::unique_ptr<ILauncher> l = std::make_unique<Launcher>();
    
    if (bool(code))
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
