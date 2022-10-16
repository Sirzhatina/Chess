#include "GameplayHandler.hpp"

 
int GameplayHandler::run()
{
    char choice;
    while (true)
    {
        dr->drawMainMenu();
        (std::cin >> choice).get();

        switch (choice)
        {
        case '1':
            play();
            break;
        case '2':
            dr->drawSettingsMenu();
            break;
        case '3':
            system("pause");
            return 0;
        default:
            continue;
        }
    }
}