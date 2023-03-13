include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(Interfaces)
add_subdirectory(Core)
add_subdirectory(Logger)
add_subdirectory(CLI)
add_subdirectory(Server)

install(TARGETS Chess.CLI Chess.Server DESTINATION ${CMAKE_SOURCE_DIR}/bin)