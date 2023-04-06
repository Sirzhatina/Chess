set(TARGET Chess.Core)

project(${TARGET} LANGUAGES CXX)

set(PIECES
    Piece/Bishop.cpp
    Piece/Bishop.ixx
    Piece/King.cpp
    Piece/King.ixx
    Piece/Knight.cpp
    Piece/Knight.ixx
    Piece/Pawn.cpp
    Piece/Pawn.ixx
    Piece/Pieces.ixx
    Piece/Piece.cpp
    Piece/Piece.ixx
    Piece/Queen.cpp
    Piece/Queen.ixx
    Piece/Rook.cpp
    Piece/Rook.ixx
)
set(SOURCES
    ${PIECES}
    Board.cpp
    Board.ixx
    # Match.cpp
    Match.ixx
    Player.cpp
    Player.ixx
    Primitives.cpp
    Primitives.ixx
    Settings.cpp
    Settings.ixx
    Timer.cpp
    Timer.ixx
)


add_library(${TARGET} SHARED ${SOURCES})

if (MSVC)
    target_compile_options(${TARGET} PUBLIC "/experimental:module")
    set_target_properties(${TARGET} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

target_link_libraries(${TARGET} Chess.Interfaces)
target_include_directories(${TARGET} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/)
