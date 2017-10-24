cmake_minimum_required(VERSION 3.6)
project(ThreeEngine)

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
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DRELEASE)
    set(EXECUTABLE_OUTPUT_PATH ${RUNTIME_OUTPUT_DIRECTORY_RELEASE})
ENDIF ()

set(SOURCE_FILES
        src/Debug.h src/Engine.cpp src/Engine.h
        src/json.hpp
        src/Math/Vector.cpp src/Math/Vector.h
        src/Math/Vector2.cpp src/Math/Vector2.h
        src/Math/Maths.cpp src/Math/Maths.h
        src/Math/Vector4.cpp src/Math/Vector4.h
        src/Math/Matrix.cpp src/Math/Matrix.h
        src/Math/TMatrix.h
        src/Math/Matrix3.cpp src/Math/Matrix3.h
        src/Math/Matrix2.cpp src/Math/Matrix2.h
        src/Shader/Shader.cpp src/Shader/Shader.h
        src/Shader/ShaderProgram.cpp src/Shader/ShaderProgram.h
        src/OpenGLUtils.h
        src/Tangram/Tangram.cpp src/Tangram/Tangram.h
        src/IActor.h
        src/Tangram/Triangle.cpp src/Tangram/Triangle.h
        src/Tangram/Square.cpp src/Tangram/Square.h
        src/Tangram/Parallelogram.cpp src/Tangram/Parallelogram.h
        src/Tangram3D/Cube.cpp src/Tangram3D/Cube.h
        src/Tangram3D/Tangram3D.cpp src/Tangram3D/Tangram3D.h)

set(TESTS_SOURCE_FILES src/Tests/catch.hpp src/Tests/tests.cpp src/Tests/VectorTests.h src/Tests/MatrixTests.h)


find_package(OpenGL REQUIRED)

if (WIN32) # WINDOWS specific properties
    add_definitions(-DOS_WIN)

    set(GLUT_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/freeglut-msvc/include")
    set(GLEW_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glew-msvc/include")
    set(GLUT_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/freeglut-msvc/lib/x64/freeglut.lib")
    set(GLEW_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glew-msvc/lib/Release/x64/glew32.lib")

elseif (APPLE)
    add_definitions(-DOS_MAC)
elseif (UNIX AND NOT APPLE)
    add_definitions(-DOS_LINUX)

    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wextra -pedantic -g3 -Og -Wuninitialized")

    find_package(GLUT REQUIRED)
    find_package(GLEW REQUIRED)

    if (NOT (OpenGL_FOUND AND GLUT_FOUND AND GLEW_FOUND))
        message(FATAL_ERROR "Some needed libraries were not found. Try running:\n\tsudo apt install freeglut3-dev libglew-dev libxmu-dev libxi-dev")
    endif ()
endif ()

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

add_executable(ThreeEngine src/main.cpp ${SOURCE_FILES})
target_link_libraries(ThreeEngine ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(ThreeEngineTests ${SOURCE_FILES} ${TESTS_SOURCE_FILES})
target_link_libraries(ThreeEngineTests ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})


if (WIN32) # WINDOWS post build

    set(GLUT_SHARED_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/freeglut-msvc/bin/x64/freeglut.dll")
    set(GLEW_SHARED_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glew-msvc/bin/Release/x64/glew32.dll")

    add_custom_command(TARGET ThreeEngine POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E echo Copying Libraries
            COMMAND ${CMAKE_COMMAND} -E copy ${GLUT_SHARED_LIBRARY} ${EXECUTABLE_OUTPUT_PATH}
            COMMAND ${CMAKE_COMMAND} -E copy ${GLEW_SHARED_LIBRARY} ${EXECUTABLE_OUTPUT_PATH}
            )

    add_custom_command(TARGET ThreeEngineTests POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E echo Copying Libraries
            COMMAND ${CMAKE_COMMAND} -E copy ${GLUT_SHARED_LIBRARY} ${EXECUTABLE_OUTPUT_PATH}
            COMMAND ${CMAKE_COMMAND} -E copy ${GLEW_SHARED_LIBRARY} ${EXECUTABLE_OUTPUT_PATH}
            )
endif ()

add_custom_command(TARGET ThreeEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo Copying Config files
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/config ${EXECUTABLE_OUTPUT_PATH}/config/
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/shaders ${EXECUTABLE_OUTPUT_PATH}/shaders/
        )
add_custom_command(TARGET ThreeEngineTests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo Copying Config files
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/config ${EXECUTABLE_OUTPUT_PATH}/config/
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/shaders ${EXECUTABLE_OUTPUT_PATH}/shaders/
        )
add_custom_target(CopyConfigFiles
        COMMAND ${CMAKE_COMMAND} -E echo Copying Config files
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/config ${EXECUTABLE_OUTPUT_PATH}/config/
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/shaders ${EXECUTABLE_OUTPUT_PATH}/shaders/
        )