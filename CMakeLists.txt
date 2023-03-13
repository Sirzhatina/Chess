cmake_minimum_required(VERSION 3.25)

project(Chess LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR}/Conan)

find_package(SFML REQUIRED)

add_subdirectory(src)
