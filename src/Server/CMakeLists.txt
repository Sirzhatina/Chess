set(TARGET Chess.Server)

project(${TARGET} LANGUAGES CXX)

set(SOURCES
    AdminCLI.cpp
    AdminCLI.hpp
    main.cpp
    Server.cpp
    Server.hpp
)

add_executable(${TARGET} ${SOURCES})

target_link_libraries(${TARGET} sfml::sfml)