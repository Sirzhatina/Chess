set(TARGET Chess.Drawer)

set(SOURCES Drawer.cpp Drawer.hpp)

add_library(${TARGET} ${SOURCES})

target_link_libraries(${TARGET} PUBLIC Chess.Core.Core)