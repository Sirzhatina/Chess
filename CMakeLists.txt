cmake_minimum_required(VERSION 3.17)

set(TARGET run)

project(Chess)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
        Game_basics.cpp
        Game_basics.hpp
        Msoftcon.cpp
        Msoftcon.h
        main.cpp
)

add_subdirectory(Core)
add_subdirectory(Logger)

add_executable(${TARGET} ${SOURCES})

target_link_libraries(${TARGET} PUBLIC Chess.Core)
