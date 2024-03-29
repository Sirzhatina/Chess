#include <iostream>
#include <Interfaces/IClient.hpp>
#include "Client.hpp"

int main()
{
    std::unique_ptr<IClient> l = std::make_unique<Client>();
    
    if (auto code = l->launch(); bool(code))
    {
        std::cerr << "Something went wrong\n";
        return int(code);
    }
    return 0;
}
