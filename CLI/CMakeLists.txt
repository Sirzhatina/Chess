set(TARGET Chess.CLI)

set(SOURCES 
    Drawer.cpp 
    Drawer.hpp
    FileDrawer.hpp
    GameplayHandler.cpp
    GameplayHandler.hpp
    IDrawer.hpp
    Launcher.hpp
)

add_library(${TARGET} ${SOURCES})

target_link_libraries(${TARGET} PUBLIC Chess.Core.Core)
