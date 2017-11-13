/*
 * File Mesh.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include <GL/glew.h>
#include <Engine/OpenGLUtils.h>
#include "Mesh.h"

#define VERTICES 0
#define COLORS 1
#define TEXCOORDS 2
#define NORMALS 3

namespace ThreeEngine {

    Mesh::Mesh() : isInitiated(false), Vertices(), Colors(), TexCoords(),
                   Normals() { }

    Mesh::~Mesh() {
        if (!isInitiated) {
            return;
        }
        glBindVertexArray(VaoId);
        glDisableVertexAttribArray(VERTICES);
        glDisableVertexAttribArray(COLORS);
        glDisableVertexAttribArray(TEXCOORDS);
        glDisableVertexAttribArray(NORMALS);
        glDeleteBuffers(1, &VboVertices);
        glDeleteBuffers(1, &VboColors);
        glDeleteBuffers(1, &VboTexcoords);
        glDeleteBuffers(1, &VboNormals);
        glDeleteVertexArrays(1, &VaoId);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        CheckOpenGLError("ERROR: Could not destroy VAOs and VBOs.");
    }

    void Mesh::Init() {
        isInitiated = true;

        glGenVertexArrays(1, &VaoId);
        glBindVertexArray(VaoId);
        {
            // Vertices
            glGenBuffers(1, &VboVertices);
            glBindBuffer(GL_ARRAY_BUFFER, VboVertices);
            glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vector),
                         &Vertices[0], GL_STATIC_DRAW);
            glEnableVertexAttribArray(VERTICES);
            glVertexAttribPointer(VERTICES, 3, GL_FLOAT, GL_FALSE,
                                  sizeof(Vector), 0);

            //Colors
            if (!Colors.empty()) {
                Colors = std::vector<Vector4>(Vertices.size(), {0, 0, 0, 1});
            }
            glGenBuffers(1, &VboColors);
            glBindBuffer(GL_ARRAY_BUFFER, VboColors);
            glBufferData(GL_ARRAY_BUFFER, Colors.size() * sizeof(Vector4),
                         &Colors[0], GL_STREAM_DRAW);
            glEnableVertexAttribArray(COLORS);
            glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE,
                                  sizeof(Vector4), 0);

            // Texture Coordinates
            if (!TexCoords.empty()) {
                glGenBuffers(1, &VboTexcoords);
                glBindBuffer(GL_ARRAY_BUFFER, VboTexcoords);
                glBufferData(GL_ARRAY_BUFFER,
                             TexCoords.size() * sizeof(Vector2), &TexCoords[0],
                             GL_STATIC_DRAW);
                glEnableVertexAttribArray(TEXCOORDS);
                glVertexAttribPointer(TEXCOORDS, 2, GL_FLOAT, GL_FALSE,
                                      sizeof(Vector2), 0);
            }

            // Normals
            if (!Normals.empty()) {
                glGenBuffers(1, &VboNormals);
                glBindBuffer(GL_ARRAY_BUFFER, VboNormals);
                glBufferData(GL_ARRAY_BUFFER, Normals.size() * sizeof(Vector),
                             &Normals[0], GL_STATIC_DRAW);
                glEnableVertexAttribArray(NORMALS);
                glVertexAttribPointer(NORMALS, 3, GL_FLOAT, GL_FALSE,
                                      sizeof(Vector), 0);
            }
        }
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        CheckOpenGLError("Could not create VAOs and VBOs.");
    }

    void Mesh::Bind() {
        glBindVertexArray(VaoId);
        CheckOpenGLError("Could not Bind Mesh.");
    }

    void Mesh::Draw() {

        glBindBuffer(GL_ARRAY_BUFFER, VboColors);
        glBufferSubData(GL_ARRAY_BUFFER, 0, Colors.size() * sizeof(Vector4),
                        &Colors[0]);

        glDrawArrays(GL_TRIANGLES, 0, Vertices.size());

        CheckOpenGLError("Could not Draw Mesh.");
    }

    void Mesh::Unbind() {
        glBindVertexArray(0);
        CheckOpenGLError("Could not Unbind Mesh.");
    }

} /* namespace Divisaction */