/*
 * File Parallelogram.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "Parallelogram3D.h"

#define VERTICES 0
#define COLORS 1

namespace ThreeEngine {

    Parallelogram3D::Parallelogram3D() : color{.5f, .1f, .1f, 1.0f}, Vertices{
            {{0.0f, 0.0f, 1.0f, 1.0f}, {0.9f, 0.0f, 0.0f, 1.0f}}, // 0 - FRONT
            {{1.0f, 0.0f, 1.0f, 1.0f}, {0.9f, 0.0f, 0.0f, 1.0f}}, // 1
            {{1.5f, 0.5f, 1.0f, 1.0f}, {0.9f, 0.0f, 0.0f, 1.0f}}, // 2
            {{1.5f, 0.5f, 1.0f, 1.0f}, {0.9f, 0.0f, 0.0f, 1.0f}}, // 2
            {{0.5f, 0.5f, 1.0f, 1.0f}, {0.9f, 0.0f, 0.0f, 1.0f}}, // 3
            {{0.0f, 0.0f, 1.0f, 1.0f}, {0.9f, 0.0f, 0.0f, 1.0f}}, // 0

            {{1.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 0.9f, 0.0f, 1.0f}}, // 1 - RIGHT
            {{1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.9f, 0.0f, 1.0f}}, // 5
            {{1.5f, 0.5f, 0.0f, 1.0f}, {0.0f, 0.9f, 0.0f, 1.0f}}, // 6
            {{1.5f, 0.5f, 0.0f, 1.0f}, {0.0f, 0.9f, 0.0f, 1.0f}}, // 6
            {{1.5f, 0.5f, 1.0f, 1.0f}, {0.0f, 0.9f, 0.0f, 1.0f}}, // 2
            {{1.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 0.9f, 0.0f, 1.0f}}, // 1

            {{1.5f, 0.5f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.9f, 1.0f}}, // 2 - TOP
            {{1.5f, 0.5f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.9f, 1.0f}}, // 6
            {{0.5f, 0.5f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.9f, 1.0f}}, // 7
            {{0.5f, 0.5f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.9f, 1.0f}}, // 7
            {{0.5f, 0.5f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.9f, 1.0f}}, // 3
            {{1.5f, 0.5f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.9f, 1.0f}}, // 2

            {{1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.9f, 0.9f, 1.0f}}, // 5 - BACK
            {{0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.9f, 0.9f, 1.0f}}, // 4
            {{0.5f, 0.5f, 0.0f, 1.0f}, {0.0f, 0.9f, 0.9f, 1.0f}}, // 7
            {{0.5f, 0.5f, 0.0f, 1.0f}, {0.0f, 0.9f, 0.9f, 1.0f}}, // 7
            {{1.5f, 0.5f, 0.0f, 1.0f}, {0.0f, 0.9f, 0.9f, 1.0f}}, // 6
            {{1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.9f, 0.9f, 1.0f}}, // 5

            {{0.0f, 0.0f, 0.0f, 1.0f}, {0.9f, 0.0f, 0.9f, 1.0f}}, // 4 - LEFT
            {{0.0f, 0.0f, 1.0f, 1.0f}, {0.9f, 0.0f, 0.9f, 1.0f}}, // 0
            {{0.5f, 0.5f, 1.0f, 1.0f}, {0.9f, 0.0f, 0.9f, 1.0f}}, // 3
            {{0.5f, 0.5f, 1.0f, 1.0f}, {0.9f, 0.0f, 0.9f, 1.0f}}, // 3
            {{0.5f, 0.5f, 0.0f, 1.0f}, {0.9f, 0.0f, 0.9f, 1.0f}}, // 7
            {{0.0f, 0.0f, 0.0f, 1.0f}, {0.9f, 0.0f, 0.9f, 1.0f}}, // 4

            {{0.0f, 0.0f, 1.0f, 1.0f}, {0.9f, 0.9f, 0.0f, 1.0f}}, // 0 - BOTTOM
            {{0.0f, 0.0f, 0.0f, 1.0f}, {0.9f, 0.9f, 0.0f, 1.0f}}, // 4
            {{1.0f, 0.0f, 0.0f, 1.0f}, {0.9f, 0.9f, 0.0f, 1.0f}}, // 5
            {{1.0f, 0.0f, 0.0f, 1.0f}, {0.9f, 0.9f, 0.0f, 1.0f}}, // 5
            {{1.0f, 0.0f, 1.0f, 1.0f}, {0.9f, 0.9f, 0.0f, 1.0f}}, // 1
            {{0.0f, 0.0f, 1.0f, 1.0f}, {0.9f, 0.9f, 0.0f, 1.0f}}  // 0
    } {
        shaderProgram = nullptr;
        transform.SetIdentity();
    }

    Parallelogram3D::Parallelogram3D(GLfloat RGBA[6][4]) : Parallelogram3D() {
        for (int i = 0; i < 6; ++i) {
            std::copy(std::begin(RGBA[i]), std::end(RGBA[i]), Vertices[i].RGBA);
        }
    }

    Parallelogram3D::~Parallelogram3D() {
        glBindVertexArray(vaoId);
        glDisableVertexAttribArray(VERTICES);
        glDisableVertexAttribArray(COLORS);
        glDeleteBuffers(1, &vboId);
        glDeleteVertexArrays(1, &vaoId);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        CheckOpenGLError("Could not destroy VAOs and VBOs.");
    }

    void Parallelogram3D::Init() {
        if (!shaderProgram) {
            shaderProgram = std::make_shared<ShaderProgram>("shaders/SimpleColor/program.json");
        }
        shaderProgram->Init();

        glGenVertexArrays(1, &vaoId);
        glBindVertexArray(vaoId);
        {
            glGenBuffers(1, &vboId);

            glBindBuffer(GL_ARRAY_BUFFER, vboId);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(VERTICES);
            glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
            glEnableVertexAttribArray(COLORS);
            glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                  (GLvoid*) sizeof(Vertices[0].XYZW));
        }
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        CheckOpenGLError("Could not create VAOs and VBOs.");

    }

    void Parallelogram3D::Draw() {
        glBindVertexArray(vaoId);
        shaderProgram->Bind();

        number matrixArray[16];
        transform.ToArray(matrixArray);
        glUniformMatrix4fv(shaderProgram->GetUniformLocationId("ModelMatrix"), 1, GL_FALSE,
                           matrixArray);
        glUniform4f(shaderProgram->GetUniformLocationId("ModelColor"), color[0], color[1], color[2],
                    color[3]);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        shaderProgram->Unbind();
        glBindVertexArray(0);

        CheckOpenGLError("ERROR: Could not draw Actor.");
    }

} /* namespace Divisaction */