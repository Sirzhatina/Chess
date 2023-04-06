cmake_minimum_required(VERSION 3.25)

project(Chess LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

if (NOT DEFINED CONAN_OUTPUT_FOLDER)
    set(CONAN_OUTPUT_FOLDER ${CMAKE_BINARY_DIR}/Conan)
endif()

if (NOT DEFINED CONAN_HOST_BUILD_PROFILE)
    set(CONAN_HOST_BUILD_PROFILE "default")
endif()

if (NOT DEFINED CONAN_TARGET_BUILD_PROFILE)
    set(CONAN_TARGET_BUILD_PROFILE ${CONAN_HOST_BUILD_PROFILE})
endif()

list(APPEND CMAKE_PREFIX_PATH ${CONAN_OUTPUT_FOLDER})

execute_process(
    COMMAND conan 
    "install"
    "--requires=sfml/2.5.1"
    "--generator=CMakeDeps"
    "--output-folder=${CONAN_OUTPUT_FOLDER}" 
    "--build=missing" 
    "--profile=${CONAN_HOST_BUILD_PROFILE}" 
    "--profile:build=${CONAN_TARGET_BUILD_PROFILE}"
    WORKING_DIRECTORY      ${CMAKE_SOURCE_DIR}
    COMMAND_ERROR_IS_FATAL ANY
)

find_package(SFML REQUIRED)

add_subdirectory(src)
