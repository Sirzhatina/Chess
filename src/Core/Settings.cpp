#include "Settings.hpp"

Settings& Settings::instance()
{
    static Settings inst;
    return inst;
}