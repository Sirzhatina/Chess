cmake_minimum_required(VERSION 3.17)

project(Chess LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
#   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
#   file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
#                 "${CMAKE_BINARY_DIR}/conan.cmake"
#                 TLS_VERIFY ON)
# endif()

# include(${CMAKE_BINARY_DIR}/conan.cmake)

# conan_cmake_run(CONANFILE conanfile.txt
#                 BASIC_SETUP CMAKE_TARGETS
#                 BUILD missing)

add_subdirectory(Interfaces)
add_subdirectory(Core)
add_subdirectory(Logger)
add_subdirectory(CLI)
