#pragma once


// entities common among other CLI-entities
namespace CLI
{
#ifdef _WIN32
    inline void clear() { std::system("cls"); }
#else
    inline void clear() { std::system("clear"); }
#endif

inline constexpr auto tab{"\t\t"};

inline constexpr auto dTab{ "\t\t\t\t" };

inline constexpr auto down{ "\n\n\n\n\n\n\n\n\n\n" };
}