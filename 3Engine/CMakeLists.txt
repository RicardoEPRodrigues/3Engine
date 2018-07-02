#cmake_minimum_required(VERSION 3.6)
cmake_minimum_required(VERSION 3.2)
project(3Engine)

# Compiler configuration

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -O0")
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

# External Libraries configuration

find_package(OpenGL REQUIRED)

if (WIN32) # WINDOWS specific properties
    add_definitions(-DOS_WIN)

    if (DEFINED MINGW)
        set(GLUT_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/freeglut-mingw/include")
        set(GLUT_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/freeglut-mingw/lib/x64/libfreeglut.a")
        set(GLEW_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glew-mingw/include")
        set(GLEW_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glew-mingw/lib/x64/libglew32.dll.a")
    else ()
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
        # SOIL
        src/SOIL/image_DXT.c src/SOIL/image_DXT.h src/SOIL/image_helper.c src/SOIL/image_helper.h src/SOIL/SOIL.c src/SOIL/SOIL.h src/SOIL/stb_image_aug.c src/SOIL/stb_image_aug.h src/SOIL/stbi_DDS_aug.h src/SOIL/stbi_DDS_aug_c.h
        src/Utilities/json.hpp
        src/Utilities/singleton.h
        src/Debug.h
        src/Engine.cpp src/Engine.h
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
        src/IDrawable.h
        src/Camera/Camera.cpp src/Camera/Camera.h
        src/Input.cpp src/Input.h
        src/Camera/LookAt.cpp src/Camera/LookAt.h
        src/Camera/Perspective.cpp src/Camera/Perspective.h
        src/Camera/Ortho.cpp src/Camera/Ortho.h
        src/Math/Quat.cpp src/Math/Quat.h
        src/Time/Time.cpp src/Time/Time.h
        src/Time/GlutTimeCalculator.cpp src/Time/GlutTimeCalculator.h
        src/Controllers/FreeCameraController.cpp src/Controllers/FreeCameraController.h
        src/Controllers/SphereCameraController.cpp src/Controllers/SphereCameraController.h
        src/Shapes/Mesh.cpp src/Shapes/Mesh.h
        src/Shapes/MeshLoader.cpp src/Shapes/MeshLoader.h
        src/Actor.cpp src/Actor.h
        src/SceneManagement/SceneGraph.cpp src/SceneManagement/SceneGraph.h
        src/Utilities/Manager.h src/Utilities/Managers.h
        src/Utilities/Simulation.cpp src/Utilities/Simulation.h
        src/Shader/Texture.cpp src/Shader/Texture.h
        src/Shader/TextureLoader.cpp src/Shader/TextureLoader.h
        src/Shader/Cubemap.cpp src/Shader/Cubemap.h
        src/Shader/ITexture.h
        src/Actors/SkySphere.cpp src/Actors/SkySphere.h
        src/Shapes/BasicShapes.cpp src/Shapes/BasicShapes.h
        )

add_library(${PROJECT_NAME} SHARED ${ENGINE_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

# Post build commands

if (WIN32) # WINDOWS post build

    if (DEFINED MINGW)
        set(GLUT_SHARED_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/freeglut-mingw/bin/x64/freeglut.dll")
        set(GLEW_SHARED_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glew-mingw/bin/x64/glew32.dll")
    else ()
        # Assuming MSVC
        set(GLUT_SHARED_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/freeglut-msvc/bin/x64/freeglut.dll")
        set(GLEW_SHARED_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glew-msvc/bin/Release/x64/glew32.dll")
    endif ()

    add_custom_command(TARGET 3Engine POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E echo Copying Libraries
            COMMAND ${CMAKE_COMMAND} -E copy ${GLUT_SHARED_LIBRARY} ${EXECUTABLE_OUTPUT_PATH}
            COMMAND ${CMAKE_COMMAND} -E copy ${GLEW_SHARED_LIBRARY} ${EXECUTABLE_OUTPUT_PATH}
            )
endif ()


add_custom_target(CopyFilesEngine
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} -E echo Copying Engine files
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../${PROJECT_NAME}/config ${EXECUTABLE_OUTPUT_PATH}/config/
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../${PROJECT_NAME}/shaders ${EXECUTABLE_OUTPUT_PATH}/shaders/
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../${PROJECT_NAME}/assets ${EXECUTABLE_OUTPUT_PATH}/assets/
        )

add_dependencies(${PROJECT_NAME} CopyFilesEngine)