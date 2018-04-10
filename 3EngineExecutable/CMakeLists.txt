#cmake_minimum_required(VERSION 3.6)
cmake_minimum_required(VERSION 3.2)
project(3EngineExecutable)

# Compiler configuration

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
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

# External Libraries configuration

if (WIN32) # WINDOWS specific properties
    add_definitions(-DOS_WIN)
elseif (APPLE)
    add_definitions(-DOS_MAC)
elseif (UNIX AND NOT APPLE)
    add_definitions(-DOS_LINUX)

    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wextra -pedantic -g3 -Og -Wuninitialized")
endif ()

# Project files and executables/libraries

set(EXECUTABLE_SOURCE_FILES
        src/main.cpp
        #        src/Tangram/Tangram.cpp src/Tangram/Tangram.h
        #        src/Tangram3D/Tangram3D.cpp src/Tangram3D/Tangram3D.h
        #        src/Quaternion/Quaternion.cpp src/Quaternion/Quaternion.h
        #        src/LoaderAndScene/LoaderAndScene.cpp src/LoaderAndScene/LoaderAndScene.h
        #        src/LoaderAndScene/ColoredActor.cpp src/LoaderAndScene/ColoredActor.h src/LoaderAndScene/MoveController.cpp src/LoaderAndScene/MoveController.h src/LoaderAndScene/TangramAnimation.cpp src/LoaderAndScene/TangramAnimation.h
        src/LightScene/LightScene.h src/LightScene/LightScene.cpp
        )

include_directories(${CMAKE_SOURCE_DIR}/3Engine/src)

add_executable(${PROJECT_NAME} ${EXECUTABLE_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} 3Engine)

# Post build commands

add_custom_target(CopyFilesExe
        COMMAND ${CMAKE_COMMAND} -E echo Copying Engine files into Executable
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../3Engine/config ${EXECUTABLE_OUTPUT_PATH}/config/
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../3Engine/shaders ${EXECUTABLE_OUTPUT_PATH}/shaders/
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../3Engine/assets ${EXECUTABLE_OUTPUT_PATH}/assets/
        COMMAND ${CMAKE_COMMAND} -E echo Copying Executable files
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/config ${EXECUTABLE_OUTPUT_PATH}/config/
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/shaders ${EXECUTABLE_OUTPUT_PATH}/shaders/
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${EXECUTABLE_OUTPUT_PATH}/assets/
        )

add_dependencies(${PROJECT_NAME} CopyFilesExe)

# AppImage Support

if (UNIX AND NOT APPLE)
    add_custom_target(AppImage
            DEPENDS ${PROJECT_NAME}
            COMMAND ${CMAKE_COMMAND} -E echo Making AppImage from path ${EXECUTABLE_OUTPUT_PATH}
            COMMAND /bin/sh "${CMAKE_CURRENT_SOURCE_DIR}/../BuildTools/AppImage/build.sh" "${EXECUTABLE_OUTPUT_PATH}" "${CMAKE_CURRENT_SOURCE_DIR}/../BuildTools/AppImage/3Engine.AppDir" "${EXECUTABLE_OUTPUT_PATH}/../AppImage"
            )
endif ()
