set(TARGET Chess.Logger)

add_library(${TARGET} ILogger.cpp ILogger.hpp)

target_link_libraries(${TARGET} PUBLIC Chess.Core.Core)