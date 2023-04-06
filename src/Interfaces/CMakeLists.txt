set(TARGET Chess.Interfaces)

set(SOURCES
    IInputHandler.ixx
    Interfaces.ixx
    IDrawer.ixx
    # IClient.hpp
    # IMenu.hpp
)

add_library(${TARGET} STATIC ${SOURCES})

if (MSVC)
    target_compile_options(${TARGET} PRIVATE "/experimental:module")
endif()

target_include_directories(${TARGET} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/)