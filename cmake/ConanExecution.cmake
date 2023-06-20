if (NOT DEFINED CONAN_OUTPUT_DIR)
    set(CONAN_OUTPUT_DIR ${CMAKE_BINARY_DIR}/Conan)
endif()

if (NOT DEFINED CONAN_PROFILE_HOST)
    set(CONAN_PROFILE_HOST "default")
endif()

if (NOT DEFINED CONAN_PROFILE_BUILD)
    set(CONAN_PROFILE_BUILD ${CONAN_PROFILE_HOST})
endif()

function(ConanInstall)

    set(DOCSTR "Tells whether to execute Conan from CMake")

    if (NOT DEFINED CONAN_ALREADY_EXECUTED)
        set(CONAN_ALREADY_EXECUTED OFF CACHE BOOL ${DOCSTR})
    endif()

    if (${CONAN_ALREADY_EXECUTED})
        return()
    endif()

    set(prefix ARG)
    set(noValue )
    set(oneValue BUILD PROFILE_HOST PROFILE_BUILD OUTPUT_DIR)
    set(multiValue REQUIRES GENERATORS)

    cmake_parse_arguments("${prefix}" "${noValue}" "${oneValue}" "${multiValue}" ${ARGN})
    
    # Handling mandatory arguments
    if (NOT DEFINED ${prefix}_REQUIRES)
        message(FATAL_ERROR "REQUIRES arguments are not specified. Consult Conan docs for details")
    endif()
    
    if(NOT DEFINED ${prefix}_GENERATORS)
        message(FATAL_ERROR "GENERATORS arguments are not specified. Consult Conan docs for details")
    endif()
    
    
    # Handling optional arguments 
    if (NOT DEFINED ${prefix}_BUILD)
        set(${prefix}_BUILD "missing")
    endif()

    if (NOT DEFINED ${prefix}_OUTPUT_DIR)
        set(${prefix}_OUTPUT_DIR ${CONAN_OUTPUT_DIR})
    endif()
    
    if (NOT DEFINED ${prefix}_PROFILE_HOST)
        set(${prefix}_PROFILE_HOST ${CONAN_PROFILE_HOST})
    endif()

    if (NOT DEFINED ${prefix}_PROFILE_BUILD)
        set(${prefix}_PROFILE_BUILD ${${prefix}_PROFILE_HOST})
    endif()

    # Transforming values into key=value pairs
    set(REQUIRES_RESULT)
    foreach(arg IN LISTS ${prefix}_REQUIRES)
        list(APPEND REQUIRES_RESULT "--requires=${arg}")
    endforeach()
    
    set(GENERATORS_RESULT)
    foreach(arg IN LISTS ${prefix}_GENERATORS)
        list(APPEND GENERATORS_RESULT "--generator=${arg}")
    endforeach()

    # Finally, the call for execution
    execute_process(
        COMMAND "conan"
            "install"
            ${REQUIRES_RESULT}
            ${GENERATORS_RESULT}
            --build=${${prefix}_BUILD};
            --output-folder=${${prefix}_OUTPUT_DIR};
            --profile:build=${${prefix}_PROFILE_BUILD};
            --profile:host=${${prefix}_PROFILE_HOST};
        WORKING_DIRECTORY      ${CMAKE_SOURCE_DIR}
        COMMAND_ERROR_IS_FATAL ANY
    )
    set(CONAN_ALREADY_EXECUTED ON CACHE BOOL ${DOCSTR} FORCE)

    list(APPEND CMAKE_PREFIX_PATH ${CONAN_OUTPUT_DIR})
endfunction()
