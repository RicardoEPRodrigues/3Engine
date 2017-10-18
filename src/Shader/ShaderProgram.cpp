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

    ShaderProgram::ShaderProgram() = default;

    ShaderProgram::~ShaderProgram() {
        for (auto it = shaders.begin(); it != shaders.end(); ++it) {
            glDetachShader(id, (*it)->id);
            CheckOpenGLError("Could not destroy shader program.");
            delete *it;
        }
        glDeleteProgram(id);
        CheckOpenGLError("Could not destroy shader program.");
        Debug::Log("Shader Program Destructor");
    }

    void ShaderProgram::Init() {
        id = glCreateProgram();
        CheckOpenGLError("Could not create shader program.");
    }

    void ShaderProgram::Add(Shader* shader) {
        shaders.push_back(shader);
        shader->programId = id;
        glAttachShader(id, shader->id);
        CheckOpenGLError("Could not attach shader to program.");
    }

    void ShaderProgram::Remove(Shader* shader) {
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

    ShaderProgram* ShaderProgram::LoadJson(nlohmann::json j) {
        ShaderProgram* program = new ShaderProgram();
        program->Init();
        if (!j["vertex"].is_null())
        {
            std::string path = j["vertex"];
            program->Add(Shader::LoadFile(GL_VERTEX_SHADER, path.c_str()));
        }
        if (!j["fragment"].is_null())
        {
            std::string path = j["fragment"];
            program->Add(Shader::LoadFile(GL_FRAGMENT_SHADER, path.c_str()));
        }
        for (json::iterator it = j["attributes"].begin(); it != j["attributes"].end(); ++it) {
            json attribute = (*it);
            std::string name = attribute[1];
            program->BindAttributeLocation(attribute[0], name.c_str());
        }
        program->Link();
        return program;
    }

    ShaderProgram* ShaderProgram::LoadJsonFile(const GLchar* filepath) {
        std::ifstream in(filepath);
        if (in.good()) {
            json jsonProgram;
            in >> jsonProgram;

            return LoadJson(jsonProgram);
        }
        else {
            Debug::Error("Unable to load shader program file.");
            exit(EXIT_FAILURE);
        }
    }
} /* namespace Divisaction */