set(TARGET Chess.Interfaces)

set(SOURCES
    IBoardDrawer.hpp
    IInputHandler.hpp
    IDrawer.hpp
    IClient.hpp
)

add_library(${TARGET} INTERFACE ${SOURCES})

target_include_directories(${TARGET} INTERFACE ${CMAKE_SOURCE_DIR}/Interfaces)
target_include_directories(${TARGET} INTERFACE ${CMAKE_SOURCE_DIR}/Core)