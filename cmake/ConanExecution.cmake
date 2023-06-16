macro(ExecuteConan)

    set(DOCSTR "Tells whether to execute Conan from CMake")

    if (NOT DEFINED CONAN_ALREADY_EXECUTED)
        set(CONAN_ALREADY_EXECUTED OFF CACHE BOOL ${DOCSTR})
    endif()

    if (NOT ${CONAN_ALREADY_EXECUTED})

        if (NOT DEFINED CONAN_OUTPUT_DIR)
            set(CONAN_OUTPUT_DIR ${CMAKE_BINARY_DIR}/Conan)
        endif()

        if (NOT DEFINED CONAN_PROFILE_HOST)
            set(CONAN_PROFILE_HOST "default")
        endif()

        if (NOT DEFINED CONAN_PROFILE_BUILD)
            set(CONAN_PROFILE_BUILD ${CONAN_PROFILE_HOST})
        endif()

        execute_process(
            COMMAND "conan"
                "install"
                "--requires=sfml/2.5.1"
                "--generator=CMakeDeps"
                "--build=missing"
                "--output-folder=${CONAN_OUTPUT_DIR}"
                "--profile:build=${CONAN_PROFILE_BUILD}"
                "--profile:host=${CONAN_PROFILE_HOST}"
            WORKING_DIRECTORY      "${CMAKE_SOURCE_DIR}"
            COMMAND_ERROR_IS_FATAL ANY
        )
        set(CONAN_ALREADY_EXECUTED ON CACHE BOOL ${DOCSTR} FORCE)

        list(APPEND CMAKE_PREFIX_PATH ${CONAN_OUTPUT_DIR})
    endif()
endmacro()