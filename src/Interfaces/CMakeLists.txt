set(TARGET Chess.Interfaces)

set(SOURCES
    IInputHandler.hpp
    IDrawer.hpp
    IClient.hpp
    IMenu.hpp
)

add_library(${TARGET} INTERFACE ${SOURCES})
