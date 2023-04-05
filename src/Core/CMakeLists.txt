set(TARGET Chess.Core)

project(${TARGET} LANGUAGES CXX)

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
    Piece/Piece.hpp
    Piece/Queen.cpp
    Piece/Queen.hpp
    Piece/Rook.cpp
    Piece/Rook.hpp
)
set(SOURCES
    ${PIECES}
    Board.cpp
    Board.hpp
    Match.cpp
    Match.hpp
    Player.cpp
    Player.hpp
    Primitives.cpp
    Primitives.hpp
    Settings.cpp
    Settings.hpp
    Timer.cpp
    Timer.hpp
)


add_library(${TARGET} SHARED ${SOURCES})

if(MSVC)
    set_target_properties(${TARGET} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

target_link_libraries(${TARGET} Chess.Interfaces)
