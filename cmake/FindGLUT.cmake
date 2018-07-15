# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#.rst:
# FindGLUT
# --------
#
# try to find glut library and include files.
#
# IMPORTED Targets
# ^^^^^^^^^^^^^^^^
#
# This module defines the :prop_tgt:`IMPORTED` targets:
#
# ``GLUT::GLUT``
#  Defined if the system has GLUT.
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module sets the following variables:
#
# ::
#
#   GLUT_INCLUDE_DIR, where to find GL/glut.h, etc.
#   GLUT_LIBRARIES, the libraries to link against
#   GLUT_FOUND, If false, do not try to use GLUT.
#
# Also defined, but not for general use are:
#
# ::
#
#   GLUT_glut_LIBRARY = the full path to the glut library.
#   GLUT_Xmu_LIBRARY  = the full path to the Xmu library.
#   GLUT_Xi_LIBRARY   = the full path to the Xi Library.

set(GLUT_ROOT_PATH "${CMAKE_HOME_DIRECTORY}/dependencies/freeglut-msvc")

find_path(GLUT_INCLUDE_DIR NAMES GL/glut.h
        PATHS ${GLUT_ROOT_PATH}/include)
find_library(GLUT_glut_LIBRARY NAMES freeglut
        PATHS
        ${OPENGL_LIBRARY_DIR}
        ${GLUT_ROOT_PATH}/lib/x64
        )

#include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLUT REQUIRED_VARS GLUT_glut_LIBRARY GLUT_INCLUDE_DIR)

if (GLUT_FOUND)
    # Is -lXi and -lXmu required on all platforms that have it?
    # If not, we need some way to figure out what platform we are on.
    set(GLUT_LIBRARIES ${GLUT_glut_LIBRARY})

    foreach (v GLUT_Xmu_LIBRARY GLUT_Xi_LIBRARY GLUT_cocoa_LIBRARY)
        if (${v})
            list(APPEND GLUT_LIBRARIES ${${v}})
        endif ()
    endforeach ()

    if (NOT TARGET GLUT::GLUT)
        add_library(GLUT::GLUT UNKNOWN IMPORTED)
        set_target_properties(GLUT::GLUT PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${GLUT_INCLUDE_DIR}")
        if (GLUT_glut_LIBRARY MATCHES "/([^/]+)\\.framework$")
            set_target_properties(GLUT::GLUT PROPERTIES
                    IMPORTED_LOCATION "${GLUT_glut_LIBRARY}/${CMAKE_MATCH_1}")
        else ()
            set_target_properties(GLUT::GLUT PROPERTIES
                    IMPORTED_LOCATION "${GLUT_glut_LIBRARY}")
        endif ()

        if (TARGET GLUT::Xmu)
            set_property(TARGET GLUT::GLUT APPEND
                    PROPERTY INTERFACE_LINK_LIBRARIES GLUT::Xmu)
        endif ()

        if (TARGET GLUT::Xi)
            set_property(TARGET GLUT::GLUT APPEND
                    PROPERTY INTERFACE_LINK_LIBRARIES GLUT::Xi)
        endif ()

        if (TARGET GLUT::Cocoa)
            set_property(TARGET GLUT::GLUT APPEND
                    PROPERTY INTERFACE_LINK_LIBRARIES GLUT::Cocoa)
        endif ()
    endif ()

    #The following deprecated settings are for backwards compatibility with CMake1.4
    set(GLUT_LIBRARY ${GLUT_LIBRARIES})
    set(GLUT_INCLUDE_PATH ${GLUT_INCLUDE_DIR})
endif ()

mark_as_advanced(
        GLUT_INCLUDE_DIR
        GLUT_glut_LIBRARY
        GLUT_Xmu_LIBRARY
        GLUT_Xi_LIBRARY
)
