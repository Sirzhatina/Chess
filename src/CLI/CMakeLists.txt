set(TARGET Chess.CLI)

set(SOURCES
    Client.cpp
    Client.hpp
    CLI.hpp
    Drawer.cpp 
    Drawer.hpp
    FileDrawer.hpp
    InputHandler.cpp
    InputHandler.hpp
    main.cpp
    MatchSettingsIO.cpp
    MatchSettingsIO.hpp
    Menu.cpp
    Menu.hpp
)

add_executable(${TARGET} ${SOURCES})

target_link_libraries(${TARGET} Chess.Core)
target_link_libraries(${TARGET} Chess.Interfaces)