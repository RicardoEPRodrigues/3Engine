#cmake_minimum_required(VERSION 3.6)
cmake_minimum_required(VERSION 3.2)
project(3Engine)


# Project files and executables/libraries

set(ENGINE_SOURCE_FILES
        src/Utilities/gamemode_client.h
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
        src/Time/SDLTimeCalculator.cpp src/Time/SDLTimeCalculator.h
        )

add_library(${PROJECT_NAME} SHARED ${ENGINE_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT})

# Post build commands

if (WIN32) # WINDOWS post build

    set(GLUT_SHARED_LIBRARY "${CMAKE_HOME_DIRECTORY}/dependencies/freeglut-msvc/bin/x64/freeglut.dll")
    set(GLEW_SHARED_LIBRARY "${CMAKE_HOME_DIRECTORY}/dependencies/glew-msvc/bin/Release/x64/glew32.dll")

    add_custom_target(CopyLibsEngine
            COMMAND ${CMAKE_COMMAND} -E echo Copying Libraries
            COMMAND ${CMAKE_COMMAND} -E copy ${GLUT_SHARED_LIBRARY} ${LIBRARY_OUTPUT_PATH}
            COMMAND ${CMAKE_COMMAND} -E copy ${GLEW_SHARED_LIBRARY} ${LIBRARY_OUTPUT_PATH}
            )
    add_dependencies(${PROJECT_NAME} CopyLibsEngine)
endif ()


add_custom_target(CopyFilesEngine
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} -E echo Copying Engine files
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/config ${EXECUTABLE_OUTPUT_PATH}/config/
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/shaders ${EXECUTABLE_OUTPUT_PATH}/shaders/
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${EXECUTABLE_OUTPUT_PATH}/assets/
        )

add_dependencies(${PROJECT_NAME} CopyFilesEngine)