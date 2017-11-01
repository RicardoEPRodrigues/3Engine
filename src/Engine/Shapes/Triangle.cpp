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

    Triangle::Triangle() : Vertices{
                                            {{0.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
                                            {{0.7071f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
                                            {{0.0f, 0.7071f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}}
                                    } {
        shaderProgram = nullptr;
        transform.SetIdentity();
    }

    Triangle::Triangle(GLfloat RGBA[3][4]) : Triangle() {
        for (int i = 0; i < 3; ++i) {
            std::copy(std::begin(RGBA[i]), std::end(RGBA[i]), Vertices[i].RGBA);
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
        if (!shaderProgram) {
            shaderProgram = std::make_shared<ShaderProgram> ("shaders/SimpleColor/program.json");
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
        }
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        CheckOpenGLError("Could not create VAOs and VBOs.");

    }

    void Triangle::Draw() {
        glBindVertexArray(vaoId);
        shaderProgram->Bind();

        number matrixArray[16];
        transform.ToArray(matrixArray);
        glUniformMatrix4fv(shaderProgram->GetUniformLocationId("Matrix"), 1, GL_FALSE, matrixArray);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        shaderProgram->Unbind();
        glBindVertexArray(0);

        CheckOpenGLError("ERROR: Could not draw Actor.");
    }

} /* namespace Divisaction */