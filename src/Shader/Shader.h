/*
 * File Shader.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_SHADER_H
#define THREEENGINE_SHADER_H

#include <GL/glew.h>

namespace ThreeEngine {

    struct Shader {
        GLuint id;

        GLenum type;

        const GLchar* code;

        GLuint programId;

        Shader(GLenum inType, const GLchar* inCode);

        virtual ~Shader();

        bool operator==(const Shader& S) const;
    };

} /* namespace Divisaction */

#endif //THREEENGINE_SHADER_H
