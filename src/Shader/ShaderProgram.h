/*
 * File ShaderProgram.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_SHADERPROGRAM_H
#define THREEENGINE_SHADERPROGRAM_H

#include <vector>
#include "Shader.h"
#include "../json.hpp"

namespace ThreeEngine {

    class ShaderProgram {
        private:
            GLuint id;
            std::vector<Shader*> shaders;
            nlohmann::json info;

            void Add(Shader* shader);

            void BindAttributeLocation(GLuint index, const GLchar* name);

            void Link();

            GLint GetUniformLocation(const GLchar* name);

            GLint GetUniformBlockIndex(const GLchar* name);

            void UniformBlockBinding(GLuint ubi, GLuint blockBinding);

        public:

            ShaderProgram();

            explicit ShaderProgram(nlohmann::json j);

            explicit ShaderProgram(const GLchar* filepath);

            virtual ~ShaderProgram();

            void LoadJson(nlohmann::json j);

            void LoadJsonFile(const GLchar* filepath);

            void Init();

            GLint GetUniformLocationId(const GLchar* name);

            GLint GetUniformBlockId(const GLchar* name);

            GLint GetUniformBlockBidingId(const GLchar* name);

            void Bind();

            void Unbind();

            friend std::ostream& operator<<(std::ostream& os, const ShaderProgram& shaderProgram) {
                os << "Shader Program " << shaderProgram.id << std::endl
                   << shaderProgram.info.dump(2) << std::endl;
                return os;
            };

            operator std::string() const {
                return "Shader Program " + std::to_string(id) + "\n" + info.dump(2) + "\n";
            }

    };

} /* namespace Divisaction */

#endif //THREEENGINE_SHADERPROGRAM_H
