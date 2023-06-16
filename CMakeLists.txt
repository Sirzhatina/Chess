cmake_minimum_required(VERSION 3.25)

project(Chess LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/ConanExecution.cmake)
ExecuteConan()

find_package(SFML REQUIRED)

add_subdirectory(src)
