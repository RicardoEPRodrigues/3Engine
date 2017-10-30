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
        src/Engine/Debug.h src/Engine/Engine.cpp src/Engine/Engine.h
        src/Engine/json.hpp
        src/Engine/Math/Vector.cpp src/Engine/Math/Vector.h
        src/Engine/Math/Vector2.cpp src/Engine/Math/Vector2.h
        src/Engine/Math/Maths.cpp src/Engine/Math/Maths.h
        src/Engine/Math/Vector4.cpp src/Engine/Math/Vector4.h
        src/Engine/Math/Matrix.cpp src/Engine/Math/Matrix.h
        src/Engine/Math/TMatrix.h
        src/Engine/Math/Matrix3.cpp src/Engine/Math/Matrix3.h
        src/Engine/Math/Matrix2.cpp src/Engine/Math/Matrix2.h
        src/Engine/Shader/Shader.cpp src/Engine/Shader/Shader.h
        src/Engine/Shader/ShaderProgram.cpp src/Engine/Shader/ShaderProgram.h
        src/Engine/OpenGLUtils.h
        src/Examples/Tangram/Tangram.cpp src/Examples/Tangram/Tangram.h
        src/Engine/IActor.h
        src/Examples/Tangram/Triangle.cpp src/Examples/Tangram/Triangle.h
        src/Examples/Tangram/Square.cpp src/Examples/Tangram/Square.h
        src/Examples/Tangram/Parallelogram.cpp src/Examples/Tangram/Parallelogram.h
        src/Examples/Tangram3D/Cube.cpp src/Examples/Tangram3D/Cube.h
        src/Engine/Camera/Camera.cpp src/Engine/Camera/Camera.h
        src/Examples/Tangram3D/Tangram3D.cpp src/Examples/Tangram3D/Tangram3D.h
        src/Examples/Tangram3D/CameraController.cpp src/Examples/Tangram3D/CameraController.h
        src/Engine/Input.cpp src/Engine/Input.h
        src/Engine/Camera/LookAt.cpp src/Engine/Camera/LookAt.h
        src/Engine/Camera/Perspective.cpp src/Engine/Camera/Perspective.h
        src/Engine/Camera/Ortho.cpp src/Engine/Camera/Ortho.h
        src/Examples/Tangram3D/Triangle3D.cpp src/Examples/Tangram3D/Triangle3D.h
        src/Examples/Tangram3D/Parallelogram3D.h src/Examples/Tangram3D/Parallelogram3D.cpp src/Engine/Math/Quat.cpp src/Engine/Math/Quat.h)

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

    FIND_PACKAGE(OpenGL REQUIRED)
    find_package(GLUT REQUIRED)
    find_package(GLEW REQUIRED)

    message(STATUS "GLEW and FreeGlut need to be installed.\nRun:\tsudo apt install freeglut3-dev libglew-dev libxmu-dev libxi-dev")
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