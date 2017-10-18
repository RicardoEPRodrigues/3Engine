/*
 * File Triangle.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "Triangle.h"
#include "../OpenGLUtils.h"

#define VERTICES 0
#define COLORS 1

namespace ThreeEngine {

    Triangle::Triangle() : Vertices({
                                            {{0.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
                                            {{0.3536f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
                                            {{0.0f, 0.3536f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}}
                                    }),
                           Indices({0, 1, 2}) {
        shaderProgram = nullptr;
        transform.SetIdentity();
    }

    Triangle::Triangle(Triangle::Vertex vertices[3]) {
        shaderProgram = nullptr;
        transform.SetIdentity();

        for (int i = 0; i < 3; ++i) {
            Vertices[i] = vertices[i];
        }
        for (int i = 0; i < 3; ++i) {
            Indices[i] = i;
        }
    }

    Triangle::~Triangle() {
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

    void Triangle::Init() {
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

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboId[1]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
        }
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        CheckOpenGLError("Could not create VAOs and VBOs.");

        if (!shaderProgram) {
            shaderProgram = ShaderProgram::LoadJsonFile("shaders/Tangram.json");
        }
        matrixUniformId = shaderProgram->GetUniformLocation("Matrix");
    }

    void Triangle::Draw() {
        glBindVertexArray(vaoId);
        shaderProgram->Use();

        number matrixArray[16];
        transform.ToArray(matrixArray);
        glUniformMatrix4fv(matrixUniformId, 1, GL_FALSE, matrixArray);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, (GLvoid*) 0);

        shaderProgram->Stop();
        glBindVertexArray(0);

        CheckOpenGLError("ERROR: Could not draw Actor.");
    }

} /* namespace Divisaction */