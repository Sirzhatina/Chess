#pragma once

#include <string>
#include <map>
#include <Core/Settings.hpp>
#include "CLI.hpp"

class MatchSettingsIO : public ISettingsIO
{
    static inline std::map<std::string, std::string> settingsPatterns
    {
        {"Time", "(0|5|10|30|60)"}
    };

    std::pair<std::string, std::string> parseInput(std::string input) const;
public:

    void showSettings()  const override;
    void inputSettings() const override;
};