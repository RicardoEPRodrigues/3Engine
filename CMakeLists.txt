cmake_minimum_required(VERSION 3.6)
project(ThreeEngine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -pedantic -g3 -Og -Wuninitialized")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")

set(RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(RUNTIME_OUTPUT_DIRECTORY_DEBUG "${RUNTIME_OUTPUT_DIRECTORY}/debug")
set(RUNTIME_OUTPUT_DIRECTORY_RELEASE "${RUNTIME_OUTPUT_DIRECTORY}/release")

IF (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(EXECUTABLE_OUTPUT_PATH ${RUNTIME_OUTPUT_DIRECTORY_DEBUG})
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(EXECUTABLE_OUTPUT_PATH ${RUNTIME_OUTPUT_DIRECTORY_RELEASE})
ENDIF ()

set(SOURCE_FILES
        src/main.cpp
        src/Debug.h src/Engine.cpp src/Engine.h
        src/json.hpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

if (NOT (OpenGL_FOUND AND GLUT_FOUND AND GLEW_FOUND))
    message(FATAL_ERROR "Some needed libraries were not found. Try running:\n\tsudo apt install freeglut3-dev libglew-dev libxmu-dev libxi-dev")
endif ()

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

add_executable(ThreeEngine ${SOURCE_FILES})

target_link_libraries(ThreeEngine ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})


if (WIN32)
    add_definitions(-DOS_WIN)
elseif (APPLE)
    add_definitions(-DOS_MAC)
elseif (UNIX AND NOT APPLE)
    add_definitions(-DOS_LINUX)
endif ()

add_custom_command(TARGET ThreeEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo Copying Config files
        COMMAND ${CMAKE_COMMAND} -E make_directory ${EXECUTABLE_OUTPUT_PATH}/config/
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/config/SetupConfig.json ${EXECUTABLE_OUTPUT_PATH}/config/
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/config/RuntimeConfig.json ${EXECUTABLE_OUTPUT_PATH}/config/
        )
add_custom_target(CopyConfigFiles
        COMMAND ${CMAKE_COMMAND} -E echo Copying Config files
        COMMAND ${CMAKE_COMMAND} -E make_directory ${EXECUTABLE_OUTPUT_PATH}/config/
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/config/SetupConfig.json ${EXECUTABLE_OUTPUT_PATH}/config/
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/config/RuntimeConfig.json ${EXECUTABLE_OUTPUT_PATH}/config/
        )