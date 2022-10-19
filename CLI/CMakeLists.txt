set(TARGET Chess.CLI)

set(SOURCES 
    Drawer.cpp 
    Drawer.hpp
    FileDrawer.hpp
    InputHandler.cpp
    InputHandler.hpp
    IDrawer.hpp
    ILauncher.hpp
    Launcher.cpp
    Launcher.hpp
)

add_library(${TARGET} ${SOURCES})

target_link_libraries(${TARGET} PUBLIC Chess.Core.Core)
