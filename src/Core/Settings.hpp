#pragma once

class ISettingsIO
{
public:

    virtual void showSettings()  const = 0;
    virtual void inputSettings() const = 0;

    virtual ~ISettingsIO() = default;
};


// settings that are being kept only for a session. Represented as a set of enum toggles.
// TODO: make them be kept independently on a session, probably as a part of local database
struct Settings
{
    static Settings& instance();
    
    struct Match
    {
        enum class Time { no_time, min_5 = 5, min_10 = 10, min_30 = 30, hour = 60 };

        Time tm;
    };

    Match m_mSettings{Match::Time::no_time};
private:

    Settings() = default;
};


