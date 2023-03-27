#include <iostream>
#include <string>
#include "Server.hpp"
#include "AdminCLI.hpp"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Fatal error: port value is not provided. Program usage: <program> <port>.";
        return EXIT_FAILURE;
    }
    AdminCLI manager{std::make_unique<Server>(std::stoi(argv[1]))};

    manager.manage();
}