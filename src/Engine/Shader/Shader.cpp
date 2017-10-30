/*
 * File Shader.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include <fstream>
#include <vector>
#include "Shader.h"
#include "../OpenGLUtils.h"

namespace ThreeEngine {

    Shader::Shader(GLenum inType, const GLchar* inCode) {
        type = inType;
        id = glCreateShader(type);
        code = inCode;
        glShaderSource(id, 1, &(code), 0);
        glCompileShader(id);
        CheckOpenGLError("Could not create shader.");

        GLint isCompiled = 0;
        glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> errorLog(static_cast<unsigned long>(maxLength));
            glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

            char* message = &errorLog[0];
            Debug::Error("Failed to compile shader");
            Debug::Error(message);

            // Provide the infolog in whatever manor you deem best.
            // Exit with failure.
            glDeleteShader(id); // Don't leak the shader.
            exit(EXIT_FAILURE);
        }
    }

    Shader::~Shader() {
        glDeleteShader(id);
        CheckOpenGLError("Could not destroy shader.");
    }

    bool Shader::operator==(const Shader& S) const {
        return id == S.id;
    }

    Shader* Shader::LoadFile(GLenum inType, const GLchar* filepath) {
        std::ifstream in(filepath);
        if (in.good()) {
            std::string contents((std::istreambuf_iterator<char>(in)),
                                 std::istreambuf_iterator<char>());
            return new Shader(inType, contents.c_str());
        } else {
            Debug::Error("Unable to load shader file.");
            exit(EXIT_FAILURE);
        }
    }

} /* namespace Divisaction */