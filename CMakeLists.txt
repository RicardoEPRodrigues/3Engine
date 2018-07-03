#cmake_minimum_required(VERSION 3.6)
cmake_minimum_required(VERSION 3.2)
project(3EngineGlobal)

# Project files and executables/libraries

set(RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_subdirectory(3Engine)

add_subdirectory(3EngineExecutable)

add_subdirectory(3EngineTests)
