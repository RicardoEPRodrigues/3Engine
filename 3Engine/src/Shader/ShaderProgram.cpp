/*
 * File ShaderProgram.cpp in project ThreeEngine
 *
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "ShaderProgram.h"
#include "../OpenGLUtils.h"
#include <fstream>

using json = nlohmann::json;
using namespace std;

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
            Add(Shader::LoadFile(GL_VERTEX_SHADER, path));
        }
        if (!info["fragment"].is_null()) {
            std::string path = info["fragment"];
            Add(Shader::LoadFile(GL_FRAGMENT_SHADER, path));
        }
        for (auto& it : info["attributes"]) {
            json attribute = it;
            GLuint location = attribute[0];
            std::string name = attribute[1];
            BindAttributeLocation(location, name.c_str());
        }
        Link();
        std::vector<std::pair<int, std::string>> uniforms;
        ExtractUniform(id, uniforms);
        for (auto& it : uniforms) {
            if (info["uniforms"].is_null()) info["uniforms"] = json({});
            info["uniforms"][it.second.c_str()] = it.first;
        }
        for (json::iterator it = info["uniformBlocks"].begin();
             it != info["uniformBlocks"].end(); ++it) {
            std::string name = it.key();
            GLint binding = (*it)[0];
            GLint index = GetUniformBlockIndex(name.c_str());
            (*it)[1] = index;
            UniformBlockBinding((GLuint)index, (GLuint)binding);
        }
        Bind();
        for (json::iterator it = info["textures"].begin();
             it != info["textures"].end(); ++it) {
            std::string name = it.key();
            GLint number = *it;
            SetTextureUnits(name, number);
        }
        Unbind();
    }

    void ShaderProgram::Add(Shader* shader) {
        shaders.push_back(shader);
        shader->programId = id;
        glAttachShader(id, shader->id);
        CheckOpenGLError("Could not attach shader to program.");
    }

    void
    ShaderProgram::BindAttributeLocation(GLuint index, const GLchar* name) {
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

    const std::string ShaderProgram::GetTypeString(GLenum type) {
        // There are many more types than are covered here, but
        // these are the most common in these examples.
        switch (type) {
            case GL_FLOAT:
                return "float";
            case GL_FLOAT_VEC2:
                return "vec2";
            case GL_FLOAT_VEC3:
                return "vec3";
            case GL_FLOAT_VEC4:
                return "vec4";
            case GL_DOUBLE:
                return "double";
            case GL_INT:
                return "int";
            case GL_UNSIGNED_INT:
                return "unsigned int";
            case GL_BOOL:
                return "bool";
            case GL_FLOAT_MAT2:
                return "mat2";
            case GL_FLOAT_MAT3:
                return "mat3";
            case GL_FLOAT_MAT4:
                return "mat4";
            default:
                return "?";
        }
    }

    std::string
    ShaderProgram::GetResourceName(int program, int type, int id, unsigned long nameLength) {
        if (nameLength <= 0)
            return "";
        std::string name(nameLength, ' ');
        glGetProgramResourceName(static_cast<GLuint>(program),
                                 static_cast<GLenum>(type),
                                 static_cast<GLuint>(id),
                                 static_cast<GLsizei>(name.length()),
                                 nullptr, &name[0]);
        name.resize(name.length() - 1);
        return name;
    }

    void ShaderProgram::ExtractUniform(int id, std::vector<std::pair<int, std::string>>& uniforms) {
        GLint numUniforms = 0;
        glGetProgramInterfaceiv(static_cast<GLuint>(id), GL_UNIFORM,
                                GL_ACTIVE_RESOURCES, &numUniforms);
        const GLenum properties[4] = {GL_BLOCK_INDEX, GL_TYPE, GL_NAME_LENGTH,
                                      GL_LOCATION};

        for (int unif = 0; unif < numUniforms; ++unif) {
            GLint values[4];
            glGetProgramResourceiv(static_cast<GLuint>(id), GL_UNIFORM,
                                   static_cast<GLuint>(unif), 4,
                                   properties, 4, nullptr, values);

            // Skip any uniforms that are in a block.
            if (values[0] != -1)
                continue;

            std::string name = GetResourceName(id, GL_UNIFORM, unif,
                                               static_cast<unsigned long>(values[2]));
            uniforms.emplace_back(values[3], name);
            CheckOpenGLWarn("Could not get Uniform Information.");
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
        if (info["uniformBlocks"].is_null() ||
            info["uniformBlocks"][name].is_null()) {
            Debug::Warn("Unable to find uniform block.");
            return -1;
        }
        return info["uniformBlocks"][name][1];
    }

    GLint ShaderProgram::GetUniformBlockBidingId(const GLchar* name) {
        if (info["uniformBlocks"].is_null() ||
            info["uniformBlocks"][name].is_null()) {
            Debug::Warn("Unable to find uniform block.");
            return -1;
        }
        return info["uniformBlocks"][name][0];
    }

    void ShaderProgram::SetTextureUnits(std::string name, GLint number) {
        glUniform1i(glGetUniformLocation(id, name.c_str()), number);
        CheckOpenGLError("Could not set texture units.");
    }
} /* namespace Divisaction */