cmake_minimum_required(VERSION 3.6)
#cmake_minimum_required(VERSION 2.8)
project(3EngineGlobal)

###############################
# Compiler configuration

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
if (TRAVIS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif ()
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")

###############################
# RPATH correct path for libs
set(CMAKE_INSTALL_RPATH "lib")
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

###############################
# Define output directories

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/debug")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/release")


if (WIN32) # WINDOWS
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/debug")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/debug")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/release")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/debug")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/debug")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/release")


    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG})
    set(LIBRARY_OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG})

else () # LINUX / MAC

    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/debug/lib")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/debug/lib")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/release/lib")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/debug/lib")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/debug/lib")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/release/lib")


    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG})
    set(LIBRARY_OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/lib)

    IF (CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_definitions(-DDEBUG)
    elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
        add_definitions(-DRELEASE)
        set(EXECUTABLE_OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE})
        set(LIBRARY_OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/lib)
    endif ()
endif ()

###############################

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_HOME_DIRECTORY}/cmake")

###############################
# OS Specific Definitions

set(CMAKE_GENERATOR "Unix Makefiles" CACHE INTERNAL "" FORCE)

if (WIN32) # WINDOWS
    set(CMAKE_GENERATOR "Visual Studio 17 2022" CACHE INTERNAL "" FORCE)

    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

    add_definitions(-DOS_WIN)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_CRT_NO_VA_START_VALIDATION)
    add_definitions(-DWINDOWS_IGNORE_PACKING_MISMATCH)

    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -W3")
elseif (APPLE) # MACOS
    add_definitions(-DOS_MAC)
elseif (UNIX AND NOT APPLE) #LINUX
    add_definitions(-DOS_LINUX)

    if (TRAVIS)
        add_definitions(-DTRAVIS)
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -pedantic -g3 -Og -Wuninitialized")
    else ()
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -pedantic -g3 -Og -Wuninitialized")
        # Uncomment to add a sanitizer
        # set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -pedantic -g3 -Og -Wuninitialized -fno-omit-frame-pointer -fsanitize=address -fsanitize=leak -fsanitize=undefined -g -fsanitize-address-use-after-scope")
    endif ()
endif ()


###############################
# Add dependencies libraries

add_definitions(-DGLEW_NO_GLU)

# External Libraries configuration

add_library(SDL2 SHARED IMPORTED)
add_library(SDL2_IMAGE SHARED IMPORTED)
#add_library(SDL2_TTF SHARED IMPORTED)
#add_library(SDL2_MIXER SHARED IMPORTED)
add_library(GLEW SHARED IMPORTED)


if (WIN32) # WINDOWS
    set_target_properties(SDL2 PROPERTIES
            IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2/lib/x64/SDL2.dll
            IMPORTED_IMPLIB "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2/lib/x64/SDL2.lib"
            )
    add_library(SDL2MAIN SHARED IMPORTED)
    set_target_properties(SDL2MAIN PROPERTIES
            IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2/lib/x64/SDL2.dll
            IMPORTED_IMPLIB "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2/lib/x64/SDL2main.lib"
            )
    set_target_properties(SDL2_IMAGE PROPERTIES
            IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2-image/lib/x64/SDL2_image.dll
            IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2-image/lib/x64/SDL2_image.lib
            )
    #    set_target_properties(SDL2_TTF PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2/lib/libSDL2_ttf.so)
    #    set_target_properties(SDL2_MIXER PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2/lib/libSDL2_mixer.so)

    set_target_properties(GLEW PROPERTIES
            IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLEW/bin/Release/x64/glew32.dll
            IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLEW/lib/Release/x64/glew32.lib
            )
else ()
    set_target_properties(SDL2 PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2/lib/libSDL2.so)
    set_target_properties(SDL2_IMAGE PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2/lib/libSDL2_image.so)
    #    set_target_properties(SDL2_TTF PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2/lib/libSDL2_ttf.so)
    #    set_target_properties(SDL2_MIXER PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2/lib/libSDL2_mixer.so)

    set_target_properties(GLEW PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLEW/lib64/libGLEW.so)
endif ()

#set(OpenGL_GL_PREFERENCE GLVND)
set(OpenGL_GL_PREFERENCE LEGACY)
find_package(OpenGL REQUIRED)

# Force Ignore GLU
IF (OpenGL_GL_PREFERENCE STREQUAL "LEGACY")
    SET(OPENGL_LIBS "${OPENGL_gl_LIBRARY}")
ELSE ()
    SET(OPENGL_LIBS "${OPENGL_opengl_LIBRARY};${OPENGL_glx_LIBRARY}")
ENDIF ()

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2/include
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLEW/include
        ${OPENGL_INCLUDE_DIRS})

if (WIN32) # WINDOWS
    include_directories(
            ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2-image/include)
endif ()

set(GRAPHIC_LIBRARIES
        SDL2
        SDL2_IMAGE
        #        SDL2_TTF
        #        SDL2_MIXER
        GLEW
        ${OPENGL_LIBS})

if (WIN32) # WINDOWS
    set(GRAPHIC_LIBRARIES
            ${GRAPHIC_LIBRARIES}
            SDL2MAIN)
endif ()

###############################
# Project files and executables/libraries

add_custom_target(Setup.sh
        COMMAND chmod 755 ${CMAKE_CURRENT_SOURCE_DIR}/Setup.sh
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/Setup.sh
        )

if (WIN32) # WINDOWS
    add_custom_target(CopyLibs
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMAND ${CMAKE_COMMAND} -E echo Copying Dependencies files
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLEW/bin/Release/x64/ ${LIBRARY_OUTPUT_PATH}
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2-image/lib/x64/ ${LIBRARY_OUTPUT_PATH}
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2/lib/x64/ ${LIBRARY_OUTPUT_PATH}
            )
else ()
    add_custom_target(CopyLibs
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMAND ${CMAKE_COMMAND} -E echo Copying Dependencies files
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLEW/lib64 ${LIBRARY_OUTPUT_PATH}
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2/lib ${LIBRARY_OUTPUT_PATH}
            )
endif ()

###############################
# Projects

add_subdirectory(3Engine)

add_subdirectory(3EngineExecutable)

add_subdirectory(3EngineTests)
