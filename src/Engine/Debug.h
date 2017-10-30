/*
 * File Debug.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_DEBUG_H
#define THREEENGINE_DEBUG_H

#include <iostream>
#include <string>
#include <sstream>

#include <cstdarg>  // For va_start, etc.
#include <memory>    // For std::unique_ptr
#include <cstring>

#include "GL/glew.h"

namespace ThreeEngine {
    class Debug {
        private:
            Debug() {}


            static std::string string_format(const std::string& fmt_str, ...) {
                int final_n, n = ((int) fmt_str.size()) *
                                 2; /* Reserve two times as much as the length of the fmt_str */
                std::unique_ptr<char[]> formatted;
                va_list ap;
                while (1) {
                    /* Wrap the plain char array into the unique_ptr */
                    formatted.reset(new char[n]);
#if OS_WIN
                    strcpy_s(&formatted[0], n, fmt_str.c_str());
#else
                    strncpy(&formatted[0], fmt_str.c_str(), n);
#endif
                    va_start(ap, fmt_str);
                    final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
                    va_end(ap);
                    if (final_n < 0 || final_n >= n)
                        n += abs(final_n - n + 1);
                    else
                        break;
                }
                return std::string(formatted.get());
            }

        public:
            static void Print(const std::string& message) {
#ifdef DEBUG
                std::cout << message << std::endl;
#endif
            }

            template<typename... Args>
            static void Print(const std::string& fmt_str, Args... args) {
#ifdef DEBUG
                Print(string_format(fmt_str, args...));
#endif
            }

            static void Log(const std::string& message) {
#ifdef DEBUG
                std::cout << "LOG: " << message << std::endl;
#endif
            }

            template<typename... Args>
            static void Log(const std::string& fmt_str, Args... args) {
#ifdef DEBUG
                Log(string_format(fmt_str, args...));
#endif
            }

            static void Warn(const std::string& message) {
#ifdef DEBUG
                std::cerr << "WARNING: " << message << std::endl;
#endif
            }

            template<typename... Args>
            static void Warn(const std::string& fmt_str, Args... args) {
#ifdef DEBUG
                Warn(string_format(fmt_str, args...));
#endif
            }

            static void Error(const std::string& message) {
                std::cerr << "ERROR: " << message << std::endl;
            }

            template<typename... Args>
            static void Error(const std::string& fmt_str, Args... args) {
                Error(string_format(fmt_str, args...));
            }

            static std::string getGLErrorMessage(GLenum errorCode) {// Taken from https://www.khronos.org/opengl/wiki/OpenGL_Error
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
                Warn(error + message);
#endif
            }

            static void GLError(GLenum errorCode) {
                std::string error = "OpenGL Error: ";
                std::string message = getGLErrorMessage(errorCode);
                Error(error + message);
            }
    };
}

#endif //THREEENGINE_DEBUG_H
