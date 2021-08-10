cmake_minimum_required(VERSION 3.17)
project(Chess)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        Chess
        main.cpp
        Piece/Piece.cpp
        Player.cpp
        Game_basics.cpp
        Square.cpp
        Board.cpp
)