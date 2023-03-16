#include <future>
#include <string>
#include "Server.hpp"

int main(int argc, char* argv[])
{

    Server server{std::stoi(argv[1])};

    server.run();
}