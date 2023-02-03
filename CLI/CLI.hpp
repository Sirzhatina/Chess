#pragma once


// entities common among other CLI-entities
namespace CLI
{
#ifdef _WIN32
    static constexpr auto clear = "cls";
#else
    static constexpr auto clear = "clear";
#endif

inline auto tab() { return "\t\t"; }

inline auto dTab() { return "\t\t\t\t"; }

inline auto down() { return "\n\n\n\n\n\n\n\n\n\n"; }
}