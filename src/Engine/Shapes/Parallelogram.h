/*
 * File Parallelogram.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_PARALLELOGRAM_H
#define THREEENGINE_PARALLELOGRAM_H

#include <GL/glew.h>
#include "../IDrawable.h"
#include "../Shader/ShaderProgram.h"
#include "../OpenGLUtils.h"
#include "Mesh.h"

namespace ThreeEngine {

    class Parallelogram : public IDrawable {

        public:

            Mesh mesh;

            std::shared_ptr<ShaderProgram> shaderProgram;

            Parallelogram();

            explicit Parallelogram(GLfloat RGBA[6][4]);

            ~Parallelogram() override;

            void Init() override;

            void Draw() override;
    };

} /* namespace Divisaction */

#endif //THREEENGINE_PARALLELOGRAM_H
