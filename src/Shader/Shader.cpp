/*
 * File Shader.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
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
    }

    Shader::~Shader() {
        glDeleteShader(id);
        CheckOpenGLError("Could not destroy shader.");
    }

    bool Shader::operator==(const Shader& S) const {
        return id == S.id;
    }

} /* namespace Divisaction */