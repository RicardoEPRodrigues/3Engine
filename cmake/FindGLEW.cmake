# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#.rst:
# FindGLEW
# --------
#
# Find the OpenGL Extension Wrangler Library (GLEW)
#
# IMPORTED Targets
# ^^^^^^^^^^^^^^^^
#
# This module defines the :prop_tgt:`IMPORTED` target ``GLEW::GLEW``,
# if GLEW has been found.
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module defines the following variables:
#
# ::
#
#   GLEW_INCLUDE_DIRS - include directories for GLEW
#   GLEW_LIBRARIES - libraries to link against GLEW
#   GLEW_FOUND - true if GLEW has been found and can be used

set(GLEW_ROOT_PATH "${CMAKE_HOME_DIRECTORY}/dependencies/glew-msvc")

set(GLEW_INCLUDE_DIR "${GLEW_ROOT_PATH}/include")

if (NOT GLEW_LIBRARY)
    find_library(GLEW_LIBRARY NAMES GLEW glew32 glew glew32s PATHS
            ${GLEW_ROOT_PATH}/lib/Release/x64)
endif ()

#include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
find_package_handle_standard_args(GLEW
        REQUIRED_VARS GLEW_LIBRARY GLEW_INCLUDE_DIR)

if (GLEW_FOUND)
    set(GLEW_INCLUDE_DIRS ${GLEW_INCLUDE_DIR})

    if (NOT GLEW_LIBRARIES)
        set(GLEW_LIBRARIES ${GLEW_LIBRARY})
    endif ()

    if (NOT TARGET GLEW::GLEW)
        add_library(GLEW::GLEW UNKNOWN IMPORTED)
        set_target_properties(GLEW::GLEW PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${GLEW_INCLUDE_DIRS}")
        set_property(TARGET GLEW::GLEW APPEND PROPERTY IMPORTED_LOCATION "${GLEW_LIBRARY}")
    endif ()
endif ()

mark_as_advanced(GLEW_INCLUDE_DIR)
