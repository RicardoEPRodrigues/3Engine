/*
 * File Tangram.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include <GL/glew.h>
#include "Tangram.h"
#include "OpenGLUtils.h"
#include "Math/Matrix.h"

#define VERTICES 0
#define COLORS 1

GLuint VaoId, VboId[2];
GLint UniformId;

namespace ThreeEngine {


    Tangram::Tangram() : Engine() {
    }

    Tangram::~Tangram() = default;

    void createBufferObjects();

    void destroyBufferObjects();

    void Tangram::OnInit() {
        shaderProgram.Init();
        shaderProgram.Add(Shader::LoadFile(GL_VERTEX_SHADER, "shaders/SimpleColor/vertex.glsl"));
        shaderProgram.Add(Shader::LoadFile(GL_FRAGMENT_SHADER, "shaders/SimpleColor/fragment.glsl"));
        shaderProgram.BindAttributeLocation(VERTICES, "in_Position");
        shaderProgram.BindAttributeLocation(COLORS, "in_Color");
        shaderProgram.Link();
        UniformId = shaderProgram.GetUniformLocation("Matrix");

        createBufferObjects();
    }


    void Tangram::OnCleanup() {
        destroyBufferObjects();
    }


/////////////////////////////////////////////////////////////////////// VAOs & VBOs

    typedef struct {
        GLfloat XYZW[4];
        GLfloat RGBA[4];
    } Vertex;

    const Vertex Vertices[] =
            {
                    {{0.25f, 0.25f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
                    {{0.75f, 0.25f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
                    {{0.50f, 0.75f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}}
            };

    const GLubyte Indices[] =
            {
                    0, 1, 2
            };

    void createBufferObjects() {
        glGenVertexArrays(1, &VaoId);
        glBindVertexArray(VaoId);
        {
            glGenBuffers(2, VboId);

            glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(VERTICES);
            glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
            glEnableVertexAttribArray(COLORS);
            glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                  (GLvoid*) sizeof(Vertices[0].XYZW));

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[1]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
        }
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        CheckOpenGLError("Could not create VAOs and VBOs.");
    }

    void destroyBufferObjects() {
        glBindVertexArray(VaoId);
        glDisableVertexAttribArray(VERTICES);
        glDisableVertexAttribArray(COLORS);
        glDeleteBuffers(2, VboId);
        glDeleteVertexArrays(1, &VaoId);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        CheckOpenGLError("Could not destroy VAOs and VBOs.");
    }

    Matrix I = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
    }; // Row Major (GLSL is Column Major)

    Matrix M = {
            1.0f, 0.0f, 0.0f, -1.0f,
            0.0f, 1.0f, 0.0f, -1.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
    }; // Row Major (GLSL is Column Major)

    void Tangram::DrawScene() {
        glBindVertexArray(VaoId);
        shaderProgram.Use();

        number identityArray[16];
        I.ToArray(identityArray);
        glUniformMatrix4fv(UniformId, 1, GL_FALSE, identityArray);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, (GLvoid*) 0);

        number translationArray[16];
        M.ToArray(translationArray);
        glUniformMatrix4fv(UniformId, 1, GL_FALSE, translationArray);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, (GLvoid*) 0);

        shaderProgram.Stop();
        glBindVertexArray(0);

        CheckOpenGLError("ERROR: Could not draw scene.");
    }

} /* namespace Divisaction */