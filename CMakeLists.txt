cmake_minimum_required(VERSION 3.17)

set(TARGET Chess)

project(${TARGET})

set(CMAKE_CXX_STANDARD 20)

set(SOURCES
        Piece\Piece.cpp
        Board.cpp
        Game_basics.cpp
        Gameplay.cpp
        main.cpp
        Msoftcon.cpp
        Player.cpp
        Traits.cpp)

set(HEADERS
        Piece\Piece.h
        Board.h
        Game_basics.h
        Gameplay.h
        IObserver.h
        Logger.h
        Msoftcon.h
        Player.h
        Traits.h)

add_executable(${TARGET} ${SOURCES} ${HEADERS})