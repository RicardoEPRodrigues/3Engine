#cmake_minimum_required(VERSION 3.6)
cmake_minimum_required(VERSION 3.2)
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

    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -pedantic -g3 -Og -Wuninitialized -fno-omit-frame-pointer -fsanitize=address -fsanitize=leak -fsanitize=undefined -g -fsanitize-address-use-after-scope")
endif ()


# External Libraries configuration

if (UNIX AND NOT APPLE)
    message(STATUS "GLEW and SDL need to be installed.")
    message(STATUS "Run:\tsudo apt install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev libglew-dev libxmu-dev libxi-dev")
endif ()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
#find_package(SDL2_ttf REQUIRED)
#find_package(SDL2_mixer REQUIRED)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        ${SDL2_MIXER_INCLUDE_DIRS}

        ${OPENGL_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS})

set(GRAPHIC_LIBRARIES
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES})

# Project files and executables/libraries

add_subdirectory(3Engine)

add_subdirectory(3EngineExecutable)

add_subdirectory(3EngineTests)
