#cmake_minimum_required(VERSION 3.6)
cmake_minimum_required(VERSION 2.8)
project(3EngineGlobal)

# Compiler configuration

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")

set(RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(RUNTIME_OUTPUT_DIRECTORY_DEBUG "${RUNTIME_OUTPUT_DIRECTORY}/debug")
set(RUNTIME_OUTPUT_DIRECTORY_RELEASE "${RUNTIME_OUTPUT_DIRECTORY}/release")

IF (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
    set(EXECUTABLE_OUTPUT_PATH ${RUNTIME_OUTPUT_DIRECTORY_DEBUG})
    set(LIBRARY_OUTPUT_PATH ${RUNTIME_OUTPUT_DIRECTORY_DEBUG}/lib)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DRELEASE)
    set(EXECUTABLE_OUTPUT_PATH ${RUNTIME_OUTPUT_DIRECTORY_RELEASE})
    set(LIBRARY_OUTPUT_PATH ${RUNTIME_OUTPUT_DIRECTORY_RELEASE}/lib)
ENDIF ()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_HOME_DIRECTORY}/cmake")

if (WIN32) # WINDOWS specific properties
    add_definitions(-DOS_WIN)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_CRT_NO_VA_START_VALIDATION)

    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -W3")
elseif (APPLE)
    add_definitions(-DOS_MAC)
elseif (UNIX AND NOT APPLE)
    add_definitions(-DOS_LINUX)

    if (TRAVIS)
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -pedantic -g3 -Og -Wuninitialized")
    else ()
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -pedantic -g3 -Og -Wuninitialized -fno-omit-frame-pointer -fsanitize=address -fsanitize=leak -fsanitize=undefined -g -fsanitize-address-use-after-scope")
    endif ()
endif ()


# External Libraries configuration

add_library(SDL2 SHARED IMPORTED)
set_target_properties(SDL2 PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2/lib/libSDL2.so)
add_library(SDL2_IMAGE SHARED IMPORTED)
set_target_properties(SDL2_IMAGE PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2/lib/libSDL2_image.so)
add_library(SDL2_TTF SHARED IMPORTED)
set_target_properties(SDL2_TTF PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2/lib/libSDL2_ttf.so)
add_library(SDL2_MIXER SHARED IMPORTED)
set_target_properties(SDL2_MIXER PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2/lib/libSDL2_mixer.so)

add_library(GLEW SHARED IMPORTED)
set_target_properties(GLEW PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLEW/lib64/libGLEW.so)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2/include
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLEW/include
        ${OPENGL_INCLUDE_DIRS})

set(GRAPHIC_LIBRARIES
        SDL2
        SDL2_IMAGE
        SDL2_TTF
        SDL2_MIXER
        GLEW
        ${OPENGL_LIBRARIES})

# Project files and executables/libraries

add_custom_target(Setup.sh
        COMMAND chmod 755 ${CMAKE_CURRENT_SOURCE_DIR}/Setup.sh
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/Setup.sh
        )

add_subdirectory(3Engine)

add_subdirectory(3EngineExecutable)

add_subdirectory(3EngineTests)
