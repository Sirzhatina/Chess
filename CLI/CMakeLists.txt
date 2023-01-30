set(TARGET Chess.CLI)

set(SOURCES
    BoardDrawer.cpp
    BoardDrawer.hpp
    CLI.hpp
    Drawer.cpp 
    Drawer.hpp
    FileDrawer.hpp
    InputHandler.cpp
    InputHandler.hpp
    Launcher.cpp
    Launcher.hpp
)

add_library(${TARGET} ${SOURCES})

target_link_libraries(${TARGET} PUBLIC Chess.Core.Core)
target_link_libraries(${TARGET} PUBLIC Chess.Interfaces)