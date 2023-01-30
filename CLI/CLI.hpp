#pragma once

#include <iostream>

// entities common among other CLI-entities
namespace CLI
{
#ifdef _WIN32
    static constexpr auto clear = "cls";
#else
    static constexpr auto clear = "clear";
#endif

inline void tab() { std::cout << "\t\t"; }
}