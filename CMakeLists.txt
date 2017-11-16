#cmake_minimum_required(VERSION 3.6)
cmake_minimum_required(VERSION 3.2)
project(ThreeEngine)

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

find_package(OpenGL REQUIRED)

if (WIN32) # WINDOWS specific properties
    add_definitions(-DOS_WIN)

    if (DEFINED MINGW)
        set(GLUT_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/freeglut-mingw/include")
        set(GLUT_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/freeglut-mingw/lib/x64/libfreeglut.a")
        set(GLEW_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glew-mingw/include")
        set(GLEW_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glew-mingw/lib/x64/libglew32.dll.a")
    else()
        # Assuming MSVC
        set(GLUT_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/freeglut-msvc/include")
        set(GLUT_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/freeglut-msvc/lib/x64/freeglut.lib")
        set(GLEW_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glew-msvc/include")
        set(GLEW_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glew-msvc/lib/Release/x64/glew32.lib")
    endif ()

elseif (APPLE)
    add_definitions(-DOS_MAC)
elseif (UNIX AND NOT APPLE)
    add_definitions(-DOS_LINUX)

    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wextra -pedantic -g3 -Og -Wuninitialized")

    find_package(GLUT REQUIRED)
    find_package(GLEW REQUIRED)

    message(STATUS "GLEW and FreeGlut need to be installed.\nRun:\tsudo apt install freeglut3-dev libglew-dev libxmu-dev libxi-dev")
endif ()

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

# Project files and executables/libraries

include_directories(src)

set(ENGINE_SOURCE_FILES
        src/Engine/Utilities/json.hpp
        src/Engine/Utilities/singleton.h
        src/Engine/Debug.h
        src/Engine/Engine.cpp src/Engine/Engine.h
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
        src/Engine/IDrawable.h
        src/Engine/Camera/Camera.cpp src/Engine/Camera/Camera.h
        src/Engine/Input.cpp src/Engine/Input.h
        src/Engine/Camera/LookAt.cpp src/Engine/Camera/LookAt.h
        src/Engine/Camera/Perspective.cpp src/Engine/Camera/Perspective.h
        src/Engine/Camera/Ortho.cpp src/Engine/Camera/Ortho.h
        src/Engine/Math/Quat.cpp src/Engine/Math/Quat.h
        src/Engine/Shapes/Triangle.cpp src/Engine/Shapes/Triangle.h
        src/Engine/Shapes/Square.cpp src/Engine/Shapes/Square.h
        src/Engine/Shapes/Parallelogram.cpp src/Engine/Shapes/Parallelogram.h
        src/Engine/Shapes/Cube.cpp src/Engine/Shapes/Cube.h
        src/Engine/Shapes/Triangle3D.cpp src/Engine/Shapes/Triangle3D.h
        src/Engine/Shapes/Parallelogram3D.h src/Engine/Shapes/Parallelogram3D.cpp
        src/Engine/Time/Time.cpp src/Engine/Time/Time.h
        src/Engine/Time/GlutTimeCalculator.cpp src/Engine/Time/GlutTimeCalculator.h
        src/Engine/Controllers/FreeCameraController.cpp src/Engine/Controllers/FreeCameraController.h
        src/Engine/Controllers/SphereCameraController.cpp src/Engine/Controllers/SphereCameraController.h
        src/Engine/Shapes/Mesh.cpp src/Engine/Shapes/Mesh.h
        src/Engine/Shapes/MeshLoader.cpp src/Engine/Shapes/MeshLoader.h
        src/Engine/Actor.cpp src/Engine/Actor.h
        src/Engine/SceneManagement/SceneGraph.cpp src/Engine/SceneManagement/SceneGraph.h
        src/Engine/Utilities/Manager.h src/Engine/Utilities/Managers.h src/Engine/Utilities/Simulation.cpp src/Engine/Utilities/Simulation.h)

set(EXECUTABLE_SOURCE_FILES
        src/Executable/main.cpp
#        src/Executable/Tangram/Tangram.cpp src/Executable/Tangram/Tangram.h
#        src/Executable/Tangram3D/Tangram3D.cpp src/Executable/Tangram3D/Tangram3D.h
#        src/Executable/Quaternion/Quaternion.cpp src/Executable/Quaternion/Quaternion.h
        src/Executable/LoaderAndScene/LoaderAndScene.cpp src/Executable/LoaderAndScene/LoaderAndScene.h
        src/Executable/LoaderAndScene/ColoredActor.cpp src/Executable/LoaderAndScene/ColoredActor.h src/Executable/LoaderAndScene/MoveController.cpp src/Executable/LoaderAndScene/MoveController.h)

set(TESTS_SOURCE_FILES src/Tests/catch.hpp src/Tests/tests.cpp src/Tests/VectorTests.h src/Tests/MatrixTests.h)

add_library(ThreeEngine SHARED ${ENGINE_SOURCE_FILES})
target_link_libraries(ThreeEngine ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(ThreeEngineExecutable ${EXECUTABLE_SOURCE_FILES})
target_link_libraries(ThreeEngineExecutable ThreeEngine)

add_executable(ThreeEngineTests ${TESTS_SOURCE_FILES})
target_link_libraries(ThreeEngineTests ThreeEngine)

# Post build commands

if (WIN32) # WINDOWS post build

    if (DEFINED MINGW)
        set(GLUT_SHARED_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/freeglut-mingw/bin/x64/freeglut.dll")
        set(GLEW_SHARED_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glew-mingw/bin/x64/glew32.dll")
    else()
        # Assuming MSVC
        set(GLUT_SHARED_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/freeglut-msvc/bin/x64/freeglut.dll")
        set(GLEW_SHARED_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glew-msvc/bin/Release/x64/glew32.dll")
    endif ()

    add_custom_command(TARGET ThreeEngine POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E echo Copying Libraries
            COMMAND ${CMAKE_COMMAND} -E copy ${GLUT_SHARED_LIBRARY} ${EXECUTABLE_OUTPUT_PATH}
            COMMAND ${CMAKE_COMMAND} -E copy ${GLEW_SHARED_LIBRARY} ${EXECUTABLE_OUTPUT_PATH}
            )
endif ()

add_custom_command(TARGET ThreeEngineExecutable POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo Copying Config files
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/config ${EXECUTABLE_OUTPUT_PATH}/config/
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/shaders ${EXECUTABLE_OUTPUT_PATH}/shaders/
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${EXECUTABLE_OUTPUT_PATH}/assets/
        )
