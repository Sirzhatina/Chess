set(TARGET Chess.Interfaces)

set(SOURCES
    IInputHandler.hpp
    IDrawer.hpp
    IClient.hpp
)

add_library(${TARGET} INTERFACE ${SOURCES})
