/*
 * File MeshLoader.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include <fstream>
#include "../Debug.h"
#include "MeshLoader.h"

namespace ThreeEngine {

    SINGLETON_IMPLEMENTATION(MeshLoader)

    void MeshLoader::OBJ_ParseVertex(MeshLoader::MeshData& meshData,
                                     std::stringstream& sin) {
        Vector v;
        sin >> v;
        meshData.vertices.push_back(v);
    }

    void MeshLoader::OBJ_ParseTexcoord(MeshLoader::MeshData& meshData,
                                       std::stringstream& sin) {
        Vector2 t;
        sin >> t;
        meshData.texCoords.push_back(t);
    }

    void MeshLoader::OBJ_ParseNormal(MeshLoader::MeshData& meshData,
                                     std::stringstream& sin) {
        Vector n;
        sin >> n;
        meshData.normals.push_back(n);
    }

    void MeshLoader::OBJ_ParseFace(MeshLoader::MeshData& meshData,
                                   std::stringstream& sin) {
        std::string token;
        for (int i = 0; i < 3; i++) {
            std::getline(sin, token, '/');
            if (!token.empty())
                meshData.vertexIdx.push_back(
                        static_cast<unsigned int&&>(std::stoi(token)));
            std::getline(sin, token, '/');
            if (!token.empty())
                meshData.texCoordIdx.push_back(
                        static_cast<unsigned int&&>(std::stoi(token)));
            std::getline(sin, token, ' ');
            if (!token.empty())
                meshData.normalIdx.push_back(
                        static_cast<unsigned int&&>(std::stoi(token)));
        }
    }

    void MeshLoader::OBJ_ParseLine(MeshLoader::MeshData& meshData,
                                   std::stringstream& sin) {
        std::string s;
        sin >> s;
        if (s.compare("v") == 0) OBJ_ParseVertex(meshData, sin);
        else if (s.compare("vt") == 0) OBJ_ParseTexcoord(meshData, sin);
        else if (s.compare("vn") == 0) OBJ_ParseNormal(meshData, sin);
        else if (s.compare("f") == 0) OBJ_ParseFace(meshData, sin);
    }

    MeshLoader::MeshData
    MeshLoader::OBJ_LoadMeshData(std::string const& filename) {
        MeshData meshData = MeshData();
        std::ifstream ifile(filename);
        if (!ifile.good()) {
            Debug::Error("Unable to open OBJ file.");
        }
        std::string line;
        while (std::getline(ifile, line)) {
            std::stringstream stream = std::stringstream(line);
            OBJ_ParseLine(meshData, stream);
        }
        return meshData;
    }

    Mesh MeshLoader::OBJ_ProcessMeshData(MeshLoader::MeshData& meshData) {
        Mesh mesh = Mesh();
        for (unsigned int i = 0; i < meshData.vertexIdx.size(); i++) {
            unsigned int vi = meshData.vertexIdx[i];
            if ((vi - 1) >= meshData.vertices.size()) {
                DebugBreakpoint();
                continue;
            }
            Vector v = meshData.vertices[vi - 1];
            mesh.Vertices.push_back(v);
            if (!meshData.texCoords.empty()) {
                unsigned int ti = meshData.texCoordIdx[i];
                Vector2 t = meshData.texCoords[ti - 1];
                mesh.TexCoords.push_back(t);
            }
            if (!meshData.normals.empty()) {
                unsigned int ni = meshData.normalIdx[i];
                Vector n = meshData.normals[ni - 1];
                mesh.Normals.push_back(n);
            }
        }
        return mesh;
    }

    Mesh MeshLoader::LoadFileOBJ(std::string const& filepath) {
        MeshData meshData = OBJ_LoadMeshData(filepath);
        return OBJ_ProcessMeshData(meshData);
    }
} // namespace ThreeEngine