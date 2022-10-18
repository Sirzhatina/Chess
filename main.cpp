#include <iostream>
#include "CLI/Launcher.hpp"
#include "CLI/ILauncher.hpp"

int main()
{
    std::unique_ptr<ILauncher> l = std::make_unique<Launcher>();
    
    if (auto code = l->launch(); bool(code))
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
