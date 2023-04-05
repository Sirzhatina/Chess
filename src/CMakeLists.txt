include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(Interfaces)
add_subdirectory(Core)
add_subdirectory(Logger)
add_subdirectory(CLI)
add_subdirectory(Server)

if (NOT DEFINED INSTALL_BIN_DIR)
    set(INSTALL_BIN_DIR ${CMAKE_SOURCE_DIR}/bin)
endif()

install(TARGETS Chess.CLI Chess.Core Chess.Server DESTINATION ${INSTALL_BIN_DIR}/$<IF:$<CONFIG:Debug>,Debug,Release>)