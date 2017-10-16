/*
 * File ShaderProgram.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "ShaderProgram.h"
#include "../OpenGLUtils.h"

namespace ThreeEngine {

    ShaderProgram::ShaderProgram() = default;

    ShaderProgram::~ShaderProgram() {
        for (auto it = shaders.begin(); it != shaders.end(); ++it) {
            glDetachShader(id, it->id);
        }
        glDeleteProgram(id);
        CheckOpenGLError("Could not destroy shader program.");
    }

    void ShaderProgram::Init() {
        id = glCreateProgram();
        CheckOpenGLError("Could not create shader program.");
    }

    void ShaderProgram::Add(Shader shader) {
        shaders.push_back(shader);
        shader.programId = id;
        glAttachShader(id, shader.id);
        CheckOpenGLError("Could not attach shader to program.");
    }

    void ShaderProgram::Remove(Shader& shader) {
        for (auto it = shaders.begin(); it != shaders.end(); ++it) {
            if ((*it) == shader) {
                shaders.erase(it);
                break;
            }
        }
    }

    void ShaderProgram::BindAttributeLocation(GLuint index, const GLchar* name) {
        glBindAttribLocation(id, index, name);
        CheckOpenGLWarn("Could not bind attribute.");
    }

    void ShaderProgram::Link() {
        glLinkProgram(id);
        CheckOpenGLError("Could not link program.");
    }

    GLint ShaderProgram::GetUniformLocation(const GLchar* name) {
        GLint uid = glGetUniformLocation(id, name);
        CheckOpenGLWarn("Could not get uniform location.");
        return uid;
    }

    void ShaderProgram::Use() {
        glUseProgram(id);
    }

    void ShaderProgram::Stop() {
        glUseProgram(0);
    }
} /* namespace Divisaction */