/*
 * File MeshLoader.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_MESHLOADER_H
#define THREEENGINE_MESHLOADER_H

#include <Engine/Utilities/singleton.h>
#include "Mesh.h"

namespace ThreeEngine {
    class MeshLoader {
        SINGLETON_HEADER(MeshLoader)

        private:
            struct MeshData {
                std::vector<Vector> vertices, normals;
                std::vector<Vector2> texCoords;
                std::vector<unsigned int> vertexIdx, texCoordIdx, normalIdx;
            };

            void OBJ_ParseVertex(MeshData& meshData, std::stringstream& sin);

            void OBJ_ParseTexcoord(MeshData& meshData, std::stringstream& sin);

            void OBJ_ParseNormal(MeshData& meshData, std::stringstream& sin);

            void OBJ_ParseFace(MeshData& meshData, std::stringstream& sin);

            void OBJ_ParseLine(MeshData& meshData, std::stringstream& sin);

            MeshData OBJ_LoadMeshData(std::string const& filename);

            Mesh OBJ_ProcessMeshData(MeshData& meshData);

        public:
            Mesh LoadFileOBJ(std::string const& filepath);
    };
} // namespace ThreeEngine

#endif //THREEENGINE_MESHLOADER_H
