/*
 * File Tangram.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include <GL/glew.h>
#include "Tangram.h"
#include "OpenGLUtils.h"

#define VERTICES 0
#define COLORS 1

GLuint VaoId, VboId[2];
GLint UniformId;

namespace ThreeEngine {


    Tangram::Tangram() : Engine() {
    }

    Tangram::~Tangram() = default;

    const GLchar* VertexShader =
            {
                    "#version 330 core\n"

                            "in vec4 in_Position;\n"
                            "in vec4 in_Color;\n"
                            "out vec4 ex_Color;\n"

                            "uniform mat4 Matrix;\n"

                            "void main(void)\n"
                            "{\n"
                            "	gl_Position = Matrix * in_Position;\n"
                            "	ex_Color = in_Color;\n"
                            "}\n"
            };

    const GLchar* FragmentShader =
            {
                    "#version 330 core\n"

                            "in vec4 ex_Color;\n"
                            "out vec4 out_Color;\n"

                            "void main(void)\n"
                            "{\n"
                            "	out_Color = ex_Color;\n"
                            "}\n"
            };

    void createBufferObjects();

    void destroyBufferObjects();

    void Tangram::OnInit() {
        shaderProgram.Init();
        shaderProgram.Add({GL_VERTEX_SHADER, VertexShader});
        shaderProgram.Add({GL_FRAGMENT_SHADER, FragmentShader});
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

/////////////////////////////////////////////////////////////////////// SCENE

    typedef GLfloat Matrix[16];

    const Matrix I = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
    }; // Row Major (GLSL is Column Major)

    const Matrix M = {
            1.0f, 0.0f, 0.0f, -1.0f,
            0.0f, 1.0f, 0.0f, -1.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
    }; // Row Major (GLSL is Column Major)

    void Tangram::DrawScene() {
        glBindVertexArray(VaoId);
        shaderProgram.Use();

        glUniformMatrix4fv(UniformId, 1, GL_TRUE, I);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, (GLvoid*) 0);

        glUniformMatrix4fv(UniformId, 1, GL_TRUE, M);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, (GLvoid*) 0);

        shaderProgram.Stop();
        glBindVertexArray(0);

        CheckOpenGLError("ERROR: Could not draw scene.");
    }

} /* namespace Divisaction */