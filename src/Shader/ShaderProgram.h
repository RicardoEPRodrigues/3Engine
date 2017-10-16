/*
 * File ShaderProgram.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_SHADERPROGRAM_H
#define THREEENGINE_SHADERPROGRAM_H

#include <vector>
#include "Shader.h"

namespace ThreeEngine {

    class ShaderProgram {
        private:
            std::vector<Shader> shaders;
        public:
            GLuint id;

            ShaderProgram();

            virtual ~ShaderProgram();

            void Init();

            void Add(Shader shader);

            void Remove(Shader& shader);

            void BindAttributeLocation(GLuint index, const GLchar* name);

            void Link();

            GLint GetUniformLocation(const GLchar* name);

            void Use();

            void Stop();
    };

} /* namespace Divisaction */

#endif //THREEENGINE_SHADERPROGRAM_H
