#include <iostream>
#include <ILauncher.hpp>
#include "CLI/Launcher.hpp"

int main()
{
    std::unique_ptr<ILauncher> l = std::make_unique<Launcher>();
    
    if (auto code = l->launch(); bool(code))
    {
        std::cerr << "Something went wrong\n";
        return int(code);
    }
    return 0;
}
