cmake_minimum_required(VERSION 3.25)

project(Chess LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/ConanExecution.cmake)
ConanInstall(
    REQUIRES
        sfml/2.5.1
        poco/1.12.4
    GENERATORS
        CMakeDeps
# Default values:
#   BUILD
#       missing
#   OUTPUT_DIR
#       ${CONAN_OUTPUT_DIR}
#   PROFILE_HOST
#       ${CONAN_PROFILE_HOST}
#   PROFILE_BUILD
#       ${CONAN_PROFILE_BUILD}
)

find_package(SFML REQUIRED)
find_package(Poco REQUIRED)

add_subdirectory(src)

install(
    TARGETS 
        Chess.CLI 
        Chess.Core 
        Chess.Server 
    DESTINATION 
        $<IF:$<CONFIG:Debug>,Debug,Release> # CMAKE_INSTALL_PREFIX is prepended here
)
