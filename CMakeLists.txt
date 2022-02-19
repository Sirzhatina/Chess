cmake_minimum_required(VERSION 3.17)

set(TARGET Chess)

project(${TARGET})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(PIECES
        Piece/Bishop.cpp
        Piece/Bishop.hpp
        Piece/King.cpp
        Piece/King.hpp
        Piece/Knight.cpp
        Piece/Knight.hpp
        Piece/Pawn.cpp
        Piece/Pawn.hpp
        Piece/Pieces.hpp
        Piece/Piece.cpp
        Piece/Piece.h
        Piece/Rook.cpp
        Piece/Rook.hpp
)
set(SOURCES
        ${PIECES}
        Board.cpp
        Board.h
        Game_basics.cpp
        Game_basics.h
        Gameplay.cpp
        Gameplay.h
        IObserver.h
        Logger.h
        main.cpp
        Msoftcon.cpp
        Msoftcon.h
        Player.cpp
        Player.h
        Primitives.cpp
        Primitives.h
)


add_executable(${TARGET} ${SOURCES})