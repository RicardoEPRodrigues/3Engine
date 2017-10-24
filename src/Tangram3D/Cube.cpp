/*
 * File Cube.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "Cube.h"

#define VERTICES 0
#define COLORS 1

namespace ThreeEngine {

    Cube::Cube() : shaderProgram(nullptr),
                   Vertices({
                                    {{0.0f, 0.0f, 1.0f, 1.0f}, {0.9f, 0.0f, 0.0f, 1.0f}}, // 0 - FRONT
                                    {{1.0f, 0.0f, 1.0f, 1.0f}, {0.9f, 0.0f, 0.0f, 1.0f}}, // 1
                                    {{1.0f, 1.0f, 1.0f, 1.0f}, {0.9f, 0.0f, 0.0f, 1.0f}}, // 2
                                    {{1.0f, 1.0f, 1.0f, 1.0f}, {0.9f, 0.0f, 0.0f, 1.0f}}, // 2
                                    {{0.0f, 1.0f, 1.0f, 1.0f}, {0.9f, 0.0f, 0.0f, 1.0f}}, // 3
                                    {{0.0f, 0.0f, 1.0f, 1.0f}, {0.9f, 0.0f, 0.0f, 1.0f}}, // 0

                                    {{1.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 0.9f, 0.0f, 1.0f}}, // 1 - RIGHT
                                    {{1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.9f, 0.0f, 1.0f}}, // 5
                                    {{1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.9f, 0.0f, 1.0f}}, // 6
                                    {{1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.9f, 0.0f, 1.0f}}, // 6
                                    {{1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.9f, 0.0f, 1.0f}}, // 2
                                    {{1.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 0.9f, 0.0f, 1.0f}}, // 1

                                    {{1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.9f, 1.0f}}, // 2 - TOP
                                    {{1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.9f, 1.0f}}, // 6
                                    {{0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.9f, 1.0f}}, // 7
                                    {{0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.9f, 1.0f}}, // 7
                                    {{0.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.9f, 1.0f}}, // 3
                                    {{1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.9f, 1.0f}}, // 2

                                    {{1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.9f, 0.9f, 1.0f}}, // 5 - BACK
                                    {{0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.9f, 0.9f, 1.0f}}, // 4
                                    {{0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.9f, 0.9f, 1.0f}}, // 7
                                    {{0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.9f, 0.9f, 1.0f}}, // 7
                                    {{1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.9f, 0.9f, 1.0f}}, // 6
                                    {{1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.9f, 0.9f, 1.0f}}, // 5

                                    {{0.0f, 0.0f, 0.0f, 1.0f}, {0.9f, 0.0f, 0.9f, 1.0f}}, // 4 - LEFT
                                    {{0.0f, 0.0f, 1.0f, 1.0f}, {0.9f, 0.0f, 0.9f, 1.0f}}, // 0
                                    {{0.0f, 1.0f, 1.0f, 1.0f}, {0.9f, 0.0f, 0.9f, 1.0f}}, // 3
                                    {{0.0f, 1.0f, 1.0f, 1.0f}, {0.9f, 0.0f, 0.9f, 1.0f}}, // 3
                                    {{0.0f, 1.0f, 0.0f, 1.0f}, {0.9f, 0.0f, 0.9f, 1.0f}}, // 7
                                    {{0.0f, 0.0f, 0.0f, 1.0f}, {0.9f, 0.0f, 0.9f, 1.0f}}, // 4

                                    {{0.0f, 0.0f, 1.0f, 1.0f}, {0.9f, 0.9f, 0.0f, 1.0f}}, // 0 - BOTTOM
                                    {{0.0f, 0.0f, 0.0f, 1.0f}, {0.9f, 0.9f, 0.0f, 1.0f}}, // 4
                                    {{1.0f, 0.0f, 0.0f, 1.0f}, {0.9f, 0.9f, 0.0f, 1.0f}}, // 5
                                    {{1.0f, 0.0f, 0.0f, 1.0f}, {0.9f, 0.9f, 0.0f, 1.0f}}, // 5
                                    {{1.0f, 0.0f, 1.0f, 1.0f}, {0.9f, 0.9f, 0.0f, 1.0f}}, // 1
                                    {{0.0f, 0.0f, 1.0f, 1.0f}, {0.9f, 0.9f, 0.0f, 1.0f}}  // 0
                            }),
                   vaoId(0) {
        transform.SetIdentity();
    }

    Cube::~Cube() {
        if (vaoId == 0) {
            return;
        }
        glBindVertexArray(vaoId);
        glDisableVertexAttribArray(VERTICES);
        glDisableVertexAttribArray(COLORS);
        glDeleteBuffers(2, vboId);
        glDeleteVertexArrays(1, &vaoId);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        CheckOpenGLError("Could not destroy VAOs and VBOs.");
    }

    void Cube::Init() {
        if (!shaderProgram) {
            shaderProgram = std::make_shared<ShaderProgram>("shaders/Color3D/program.json");
        }
        shaderProgram->Init();

        glGenVertexArrays(1, &vaoId);
        glBindVertexArray(vaoId);
        {
            glGenBuffers(2, vboId);

            glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(VERTICES);
            glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
            glEnableVertexAttribArray(COLORS);
            glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                  (GLvoid*) sizeof(Vertices[0].XYZW));

            glBindBuffer(GL_UNIFORM_BUFFER, vboId[1]);
            glBufferData(GL_UNIFORM_BUFFER, sizeof(glMatrix) * 2, 0, GL_STREAM_DRAW);
            glBindBufferBase(GL_UNIFORM_BUFFER,
                             (GLuint) shaderProgram->GetUniformBlockBidingId("SharedMatrices"),
                             vboId[1]);
        }
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        CheckOpenGLError("Could not create VAOs and VBOs.");

    }


    const glMatrix I = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
    };

    const glMatrix ModelMatrix = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 1.0f
    }; // Column Major

// Eye(5,5,5) Center(0,0,0) Up(0,1,0)
    const glMatrix ViewMatrix1 = {
            0.70f, -0.41f, 0.58f, 0.00f,
            0.00f, 0.82f, 0.58f, 0.00f,
            -0.70f, -0.41f, 0.58f, 0.00f,
            0.00f, 0.00f, -8.70f, 1.00f
    }; // Column Major

// Eye(-5,-5,-5) Center(0,0,0) Up(0,1,0)
    const glMatrix ViewMatrix2 = {
            -0.70f, -0.41f, -0.58f, 0.00f,
            0.00f, 0.82f, -0.58f, 0.00f,
            0.70f, -0.41f, -0.58f, 0.00f,
            0.00f, 0.00f, -8.70f, 1.00f
    }; // Column Major

// Orthographic LeftRight(-2,2) TopBottom(-2,2) NearFar(1,10)
    const glMatrix ProjectionMatrix1 = {
            0.50f, 0.00f, 0.00f, 0.00f,
            0.00f, 0.50f, 0.00f, 0.00f,
            0.00f, 0.00f, -0.22f, 0.00f,
            0.00f, 0.00f, -1.22f, 1.00f
    }; // Column Major

// Perspective Fovy(30) Aspect(640/480) NearZ(1) FarZ(10)
    const glMatrix ProjectionMatrix2 = {
            2.79f, 0.00f, 0.00f, 0.00f,
            0.00f, 3.73f, 0.00f, 0.00f,
            0.00f, 0.00f, -1.22f, -1.00f,
            0.00f, 0.00f, -2.22f, 0.00f
    }; // Column Major

    void Cube::Draw() {
        // TODO implement view and projection in object
        glBindBuffer(GL_UNIFORM_BUFFER, vboId[1]);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Matrix), ViewMatrix1);
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(Matrix), sizeof(Matrix), ProjectionMatrix2);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        glBindVertexArray(vaoId);
        shaderProgram->Bind();

        number matrixArray[16];
        transform.ToArray(matrixArray);
        glUniformMatrix4fv(shaderProgram->GetUniformLocationId("ModelMatrix"), 1, GL_FALSE,
                           matrixArray);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        shaderProgram->Unbind();
        glBindVertexArray(0);

        CheckOpenGLError("ERROR: Could not draw Actor.");
    }

} /* namespace Divisaction */