//
// Created by ricardo on 10/16/17.
//

#ifndef THREEENGINE_OPENGLUTILS_H
#define THREEENGINE_OPENGLUTILS_H

#include <string>
#include <GL/glew.h>
#include "Debug.h"

namespace ThreeEngine {

    inline void CheckOpenGLError(const std::string& message = "") {
#ifdef DEBUG
        bool isError = false;
        GLenum err_code;
        while ((err_code = glGetError()) != GL_NO_ERROR) {
            Debug::Error(message);
            Debug::GLError(err_code);
            isError = true;
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
