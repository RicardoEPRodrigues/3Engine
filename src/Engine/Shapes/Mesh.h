/*
 * File Mesh.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_MESH_H
#define THREEENGINE_MESH_H

#include <vector>
#include <string>
#include <GL/glew.h>

#include "../IDrawable.h"
#include "../Math/Vector.h"
#include "../Math/Vector2.h"
#include "../Math/Vector4.h"

namespace ThreeEngine {

    class Mesh : public IDrawable {
        private:
            bool isInitiated;

            GLuint VaoId, VboVertices, VboColors, VboTexcoords, VboNormals;

        public:
            std::vector <Vector> Vertices;
            std::vector <Vector4> Colors;
            std::vector <Vector2> TexCoords;
            std::vector <Vector> Normals;

            Mesh();

            ~Mesh() override;

            void Init() override;

            void Bind();

            void Draw() override;

            void Unbind();
    };

} /* namespace Divisaction */

#endif //THREEENGINE_MESH_H
