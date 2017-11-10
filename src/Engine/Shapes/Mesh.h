/*
 * File Mesh.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_MESH_H
#define THREEENGINE_MESH_H

#include <vector>
#include <string>

#include "../IDrawable.h"
#include "../Math/Vector.h"
#include "../Math/Vector2.h"
#include "../Math/Vector4.h"

namespace ThreeEngine {

    class Mesh : public IDrawable {
        private:
            GLuint VaoId, VboVertices, VboColors, VboTexcoords, VboNormals;

            bool ColorsLoaded, TexcoordsLoaded, NormalsLoaded;

        public:
            std::vector <Vector> Vertices;
            std::vector <Vector4> Colors;
            std::vector <Vector2> Texcoords;
            std::vector <Vector> Normals;

            Mesh();

            ~Mesh() override;

            void Init() override;

            void Bind();

            void Draw() override;

            void Unbid();

            static std::vector<Mesh*> LoadMeshes(const std::string& filepath);
    };

} /* namespace Divisaction */

#endif //THREEENGINE_MESH_H
