cmake_minimum_required(VERSION 3.6)
#cmake_minimum_required(VERSION 2.8)
project(3EngineTests)

# Project files and executables/libraries

set(TESTS_SOURCE_FILES
        src/catch.hpp
        src/tests.cpp
        src/VectorTests.h
        src/MatrixTests.h)

add_executable(3EngineTests ${TESTS_SOURCE_FILES})
target_link_libraries(3EngineTests 3Engine)

# Post build commands

add_custom_target(CopyFilesTests
#        COMMAND ${CMAKE_COMMAND} -E echo Copying Engine files into Executable
#        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../3Engine/config ${EXECUTABLE_OUTPUT_PATH}/config/
#        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../3Engine/shaders ${EXECUTABLE_OUTPUT_PATH}/shaders/
#        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../3Engine/assets ${EXECUTABLE_OUTPUT_PATH}/assets/
        COMMAND ${CMAKE_COMMAND} -E echo Copying Executable files
#        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/config ${EXECUTABLE_OUTPUT_PATH}/config/
#        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/shaders ${EXECUTABLE_OUTPUT_PATH}/shaders/
#        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${EXECUTABLE_OUTPUT_PATH}/assets/
        )

add_dependencies(${PROJECT_NAME} CopyFilesTests)