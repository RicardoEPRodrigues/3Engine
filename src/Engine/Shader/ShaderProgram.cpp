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
        for (json::iterator it = info["uniformBlocks"].begin(); it != info["uniformBlocks"].end(); ++it) {
            std::string name = it.key();
            (*it)[0] = GetUniformBlockIndex(name.c_str());
            UniformBlockBinding((*it)[0], (*it)[1]);
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

        GLint isLinked = 0;
        glGetProgramiv(id, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> errorLog(static_cast<unsigned long>(maxLength));
            glGetProgramInfoLog(id, maxLength, &maxLength, &errorLog[0]);

            char* message = &errorLog[0];
            Debug::Error("Failed to compile shader");
            Debug::Error(message);

            // Provide the infolog in whatever manor you deem best.
            // Exit with failure.
            glDeleteProgram(id); // Don't leak the shader.
            exit(EXIT_FAILURE);
        }
    }

    GLint ShaderProgram::GetUniformLocation(const GLchar* name) {
        GLint uid = glGetUniformLocation(id, name);
        CheckOpenGLWarn("Could not get uniform location.");
        return uid;
    }

    GLint ShaderProgram::GetUniformBlockIndex(const GLchar* name) {
        GLint uid = glGetUniformBlockIndex(id, name);
        CheckOpenGLWarn("Could not get uniform block index.");
        return uid;
    }

    void ShaderProgram::UniformBlockBinding(GLuint ubi, GLuint blockBinding) {
        glUniformBlockBinding(id, ubi, blockBinding);
        CheckOpenGLWarn("Could not bind uniform block.");
    }

    void ShaderProgram::Bind() {
        glUseProgram(id);
    }

    void ShaderProgram::Unbind() {
        glUseProgram(0);
    }

    GLint ShaderProgram::GetUniformLocationId(const GLchar* name) {
        if (info["uniforms"].is_null() || info["uniforms"][name].is_null()) {
            Debug::Warn("Unable to find uniform location id.");
            return -1;
        }
        return info["uniforms"][name];
    }

    GLint ShaderProgram::GetUniformBlockId(const GLchar* name) {
        if (info["uniformBlocks"].is_null() || info["uniformBlocks"][name].is_null()) {
            Debug::Warn("Unable to find uniform block.");
            return -1;
        }
        return info["uniformBlocks"][name][0];
    }

    GLint ShaderProgram::GetUniformBlockBidingId(const GLchar* name) {
        if (info["uniformBlocks"].is_null() || info["uniformBlocks"][name].is_null()) {
            Debug::Warn("Unable to find uniform block.");
            return -1;
        }
        return info["uniformBlocks"][name][1];
    }
} /* namespace Divisaction */