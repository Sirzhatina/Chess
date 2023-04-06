module Settings;

Settings& Settings::instance()
{
    static Settings inst;
    return inst;
}