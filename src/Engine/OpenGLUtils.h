//
// Created by ricardo on 10/16/17.
//

#ifndef THREEENGINE_OPENGLUTILS_H
#define THREEENGINE_OPENGLUTILS_H

#include <string>
#include <GL/glew.h>
#include "Debug.h"

#ifndef GL_CONTEXT_LOST
#define GL_CONTEXT_LOST 0x0507
#endif

namespace ThreeEngine {

    typedef struct {
        GLfloat XYZW[4];
        GLfloat RGBA[4];
    } Vertex;

    typedef GLfloat glMatrix[16];

    static std::string getGLErrorMessage(GLenum errorCode) {
        // Taken from https://www.khronos.org/opengl/wiki/OpenGL_Error
        std::string message;
        switch (errorCode) {
            case GL_INVALID_ENUM:
                message += "Invalid Enumeration: Enumeration parameter is not legal enumeration for function.";
                break;
            case GL_INVALID_VALUE:
                message += "Invalid Value: Value parameter is not legal value for function.";
                break;
            case GL_INVALID_OPERATION:
                message += "Invalid Operation: the set of state for the command is not legal for the parameters given to that command.";
                break;
            case GL_STACK_OVERFLOW:
                message += "Stack Overflow: Stack pushing operation cannot be done because it would overflow the limit of that stack's size.";
                break;
            case GL_STACK_UNDERFLOW:
                message += "Stack Underflow: Stack popping operation cannot be done because the stack is already at its lowest point.";
                break;
            case GL_OUT_OF_MEMORY:
                message += "Out Of Memory: Memory cannot be allocated.";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                message += "Invalid Framebuffer Operation \" + errorCode + \" : Attempt to read from or write/render to a framebuffer that is not complete.";
                break;
            case GL_CONTEXT_LOST:
                message += "Context Lost: OpenGL context has been lost due to a graphics card reset.";
                break;
            default:
                message += "Unknown: Error Code " + errorCode;
                break;
        }
        return message;
    }

    static void GLWarn(GLenum errorCode) {
#ifdef DEBUG
        std::string error = "OpenGL Warning: ";
        std::string message = getGLErrorMessage(errorCode);
        Debug::Warn(error + message);
#endif
    }

    static void GLError(GLenum errorCode) {
        std::string error = "OpenGL Error: ";
        std::string message = getGLErrorMessage(errorCode);
        Debug::Error(error + message);
    }

    inline void CheckOpenGLError(const std::string& message = "") {
#ifdef DEBUG
        bool isError = false;
        unsigned int numberOfTries = 0;
        GLenum err_code;
        while ((err_code = glGetError()) != GL_NO_ERROR) {
            Debug::Error(message);
            GLError(err_code);
            isError = true;
            if (++numberOfTries >= 50) {
                break;
            }
        }
        if (isError) {
            DebugBreakpoint();
            exit(EXIT_FAILURE);
        }
#endif
    }

    inline void CheckOpenGLWarn(const std::string& message = "") {
#ifdef DEBUG
        GLenum err_code;
        while ((err_code = glGetError()) != GL_NO_ERROR) {
            Debug::Warn(message);
            GLWarn(err_code);
        }
#endif
    }

}

#endif //THREEENGINE_OPENGLUTILS_H
