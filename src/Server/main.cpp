#include <iostream>
#include <string>
#include "Server.hpp"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Fatal error: port value is not provided. Program usage: <program> <port>.";
        return EXIT_FAILURE;
    }
    Server server(std::stoi(argv[1]));

    auto status = server.run();
}