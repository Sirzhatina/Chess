include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(Interfaces)
add_subdirectory(Core)
add_subdirectory(Logger)
add_subdirectory(CLI)

install(TARGETS Chess.CLI DESTINATION ${CMAKE_SOURCE_DIR}/bin)