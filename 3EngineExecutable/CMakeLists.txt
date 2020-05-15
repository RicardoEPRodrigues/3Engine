#cmake_minimum_required(VERSION 3.6)
cmake_minimum_required(VERSION 2.8)
project(3EngineExecutable)

# Project files and executables/libraries

add_executable(LightScene src/LightScene/LightScene.h src/LightScene/LightScene.cpp)
target_link_libraries(LightScene ${GRAPHIC_LIBRARIES} 3Engine)

add_executable(TimeShaders src/TimeShaders/MyEngine.h src/TimeShaders/MyEngine.cpp)
target_link_libraries(TimeShaders ${GRAPHIC_LIBRARIES} 3Engine)

add_executable(Tangram3D src/Tangram3D/Tangram3D.h src/Tangram3D/Tangram3D.cpp)
target_link_libraries(Tangram3D ${GRAPHIC_LIBRARIES} 3Engine)

# Post build commands

add_custom_target(CopyFilesExe
        COMMAND ${CMAKE_COMMAND} -E echo Copying Executable files
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/config ${EXECUTABLE_OUTPUT_PATH}/config
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/shaders ${EXECUTABLE_OUTPUT_PATH}/shaders
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${EXECUTABLE_OUTPUT_PATH}/assets
        )

add_dependencies(LightScene CopyFilesExe)
add_dependencies(TimeShaders CopyFilesExe)
add_dependencies(Tangram3D CopyFilesExe)

# AppImage Support

if (UNIX AND NOT APPLE)
    add_custom_target(AppImage
            DEPENDS LightScene
            COMMAND ${CMAKE_COMMAND} -E echo Making AppImage from path ${EXECUTABLE_OUTPUT_PATH}
            COMMAND /bin/bash "${CMAKE_HOME_DIRECTORY}/BuildTools/AppImage/build.sh" "${EXECUTABLE_OUTPUT_PATH}" "${CMAKE_HOME_DIRECTORY}/BuildTools/AppImage/3Engine.AppDir" "${RUNTIME_OUTPUT_DIRECTORY}/AppImage" "${CMAKE_CURRENT_SOURCE_DIR}/../dependencies"
            )
endif ()