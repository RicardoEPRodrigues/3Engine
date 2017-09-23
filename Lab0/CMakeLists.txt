cmake_minimum_required(VERSION 3.6)
project(ThreeEngine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -pedantic -g3 -Og -Wuninitialized")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")

set(SOURCE_FILES
        src/1-StartingOpenGL.cpp
        )

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