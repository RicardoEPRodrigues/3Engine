#cmake_minimum_required(VERSION 3.6)
cmake_minimum_required(VERSION 2.8)
project(3EngineExecutable)

add_custom_target(CopyFilesExe DEPENDS CopyFilesEngine
        COMMAND ${CMAKE_COMMAND} -E echo Copying Executable files
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/config ${EXECUTABLE_OUTPUT_PATH}/config
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/shaders ${EXECUTABLE_OUTPUT_PATH}/shaders
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${EXECUTABLE_OUTPUT_PATH}/assets
        )

# Project files and executables/libraries


#add_executable(Application src/LightScene/LightScene.h src/LightScene/LightScene.cpp)
#add_executable(Application src/TimeShaders/MyEngine.h src/TimeShaders/MyEngine.cpp)
#add_executable(Application src/Tangram3D/Tangram3D.h src/Tangram3D/Tangram3D.cpp)
#add_executable(Application AVT-project-01/src/main.h AVT-project-01/src/main.cpp)
add_executable(Application CGJ-project-01/src/main.h CGJ-project-01/src/main.cpp)
target_link_libraries(Application ${GRAPHIC_LIBRARIES} 3Engine)
add_dependencies(Application CopyFilesExe)

# AppImage Support

if (UNIX AND NOT APPLE)
    add_custom_target(AppImage
            DEPENDS Application
            COMMAND ${CMAKE_COMMAND} -E echo Making AppImage from path ${EXECUTABLE_OUTPUT_PATH}
            COMMAND /bin/bash "${CMAKE_HOME_DIRECTORY}/BuildTools/AppImage/build.sh" "${EXECUTABLE_OUTPUT_PATH}" "${CMAKE_HOME_DIRECTORY}/BuildTools/AppImage/3Engine.AppDir" "${RUNTIME_OUTPUT_DIRECTORY}/AppImage" "${CMAKE_CURRENT_SOURCE_DIR}/../dependencies"
            )
endif ()