set(TARGET Chess.Core.Core)

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

add_library(${TARGET} STATIC ${SOURCES})

target_link_libraries(${TARGET} PUBLIC Chess.Interfaces)

target_include_directories(${TARGET} INTERFACE ${CMAKE_SOURCE_DIR}/Core)