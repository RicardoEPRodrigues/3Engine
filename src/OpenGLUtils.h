//
// Created by ricardo on 10/16/17.
//

#ifndef THREEENGINE_OPENGLUTILS_H
#define THREEENGINE_OPENGLUTILS_H

#include <string>
#include <GL/glew.h>
#include "Debug.h"

#if defined DEBUG && defined OS_LINUX

#include <csignal>

#endif

namespace ThreeEngine {

    inline void DebugBreakpoint() {
#ifdef DEBUG
#if OS_WIN
        __debugbreak();
#else
        std::raise(SIGINT);
#endif
#endif
    }

    inline void CheckOpenGLError(const std::string& message = "") {
#ifdef DEBUG
        bool isError = false;
        unsigned int numberOfTries = 0;
        GLenum err_code;
        while ((err_code = glGetError()) != GL_NO_ERROR) {
            Debug::Error(message);
            Debug::GLError(err_code);
            isError = true;
            if (++numberOfTries >= 50) {
                break;
            }
        }
        if (isError) {
            exit(EXIT_FAILURE);
        }
#endif
    }

    inline void CheckOpenGLWarn(const std::string& message = "") {
#ifdef DEBUG
        GLenum err_code;
        while ((err_code = glGetError()) != GL_NO_ERROR) {
            Debug::Warn(message);
            Debug::GLWarn(err_code);
        }
#endif
    }

}

#endif //THREEENGINE_OPENGLUTILS_H
