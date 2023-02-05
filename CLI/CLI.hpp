#pragma once


// entities common among other CLI-entities
namespace CLI
{
#ifdef _WIN32
    static constexpr auto clear = "cls";
#else
    static constexpr auto clear = "clear";
#endif

inline auto tab{"\t\t"};

inline auto dTab{ "\t\t\t\t" };

inline auto down{ "\n\n\n\n\n\n\n\n\n\n" };
}