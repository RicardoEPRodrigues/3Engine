/*
 * File ShaderProgram.cpp in project ThreeEngine
 *
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "ShaderProgram.h"
#include "../OpenGLUtils.h"
#include <fstream>

using json = nlohmann::json;

namespace ThreeEngine {

    ShaderProgram::ShaderProgram() : id(0), shaders(), info() {}

    ShaderProgram::ShaderProgram(nlohmann::json j) : ShaderProgram() {
        LoadJson(j);
    }

    ShaderProgram::ShaderProgram(const GLchar* filepath) : ShaderProgram() {
        LoadJsonFile(filepath);
    }

    ShaderProgram::~ShaderProgram() {
        for (auto& shader : shaders) {
            glDetachShader(id, shader->id);
            CheckOpenGLError("Could not destroy shader program.");
            delete shader;
        }
        glDeleteProgram(id);
        CheckOpenGLError("Could not destroy shader program.");
    }

    void ShaderProgram::LoadJson(nlohmann::json j) {
        info = std::move(j);
    }

    void ShaderProgram::LoadJsonFile(const GLchar* filepath) {
        std::ifstream in(filepath);
        if (in.good()) {
            json jsonProgram;
            in >> jsonProgram;

            return LoadJson(jsonProgram);
        } else {
            Debug::Error("Unable to load shader program file.");
            exit(EXIT_FAILURE);
        }
    }

    void ShaderProgram::Init() {
        if (info.is_null()) {
            Debug::Warn("No shader program information was found.");
            DebugBreakpoint();
        }
        if (id > 0) {
            // The program has already been initialized.
            return;
        }

        id = glCreateProgram();
        CheckOpenGLError("Could not create shader program.");
        if (!info["vertex"].is_null()) {
            std::string path = info["vertex"];
            Add(Shader::LoadFile(GL_VERTEX_SHADER, path.c_str()));
        }
        if (!info["fragment"].is_null()) {
            std::string path = info["fragment"];
            Add(Shader::LoadFile(GL_FRAGMENT_SHADER, path.c_str()));
        }
        for (auto& it : info["attributes"]) {
            json attribute = it;
            std::string name = attribute[1];
            BindAttributeLocation(attribute[0], name.c_str());
        }
        Link();
        for (json::iterator it = info["uniforms"].begin(); it != info["uniforms"].end(); ++it) {
            std::string name = it.key();
            (*it) = GetUniformLocation(name.c_str());
        }
    }

    void ShaderProgram::Add(Shader* shader) {
        shaders.push_back(shader);
        shader->programId = id;
        glAttachShader(id, shader->id);
        CheckOpenGLError("Could not attach shader to program.");
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

    void ShaderProgram::Bind() {
        glUseProgram(id);
    }

    void ShaderProgram::Unbind() {
        glUseProgram(0);
    }

    GLint ShaderProgram::GetUniformLocationId(const GLchar* name) {
        if (info["uniforms"][name].is_null()) {
            Debug::Warn("Unable to find uniform location id");
            return -1;
        }
        return info["uniforms"][name];
    }
} /* namespace Divisaction */