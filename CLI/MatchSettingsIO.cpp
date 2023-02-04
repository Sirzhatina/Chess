#include "MatchSettingsIO.hpp"
#include <iostream>
#include <regex>

std::pair<std::string, std::string> MatchSettingsIO::parseInput(std::string input) const
{
    std::regex pattern;
    for (const auto& [setting, value] : settingsPatterns)
    {
        pattern = setting + ": " + value;
        if (std::regex_match(input, pattern))
        {
            return {setting, input.substr(input.find_first_of(' ') + 1)};
        }
    }
    return {};
}

void MatchSettingsIO::showSettings() const
{
    auto convertSetting = [](const std::string& setting)
    {
        if (setting == "Time")
        {
            return std::to_string(int(Settings::instance().m_mSettings.tm));
        }
        return std::string{};
    };

    system(CLI::clear);
    std::cout << CLI::down() << CLI::dTab() << "[MATCH SETTINGS]\n";
    for (const auto& [key, value] : settingsPatterns)
    {
        std::cout << CLI::dTab() << CLI::tab() << key << ": " << convertSetting(key) << '\n';
    }
    std::cout << CLI::dTab() << "Input: ";
}

void MatchSettingsIO::inputSettings() const
{
    auto assignSetting = [](const std::string& setting, std::string value)
    {
        if (setting == "Time")
        {
            Settings::instance().m_mSettings.tm = Settings::Match::Time(std::stoi(value));
        }
    };

    std::string result;
    std::getline(std::cin, result);

    if (auto parsed = parseInput(std::move(result)); parsed != std::pair<std::string, std::string>{})
    {
        assignSetting(parsed.first, parsed.second);
    }
}