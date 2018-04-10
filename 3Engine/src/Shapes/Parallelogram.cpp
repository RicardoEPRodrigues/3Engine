/*
 * File Parallelogram.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "Parallelogram.h"

#define VERTICES 0
#define COLORS 1

namespace ThreeEngine {

    Parallelogram::Parallelogram()
            : IDrawable(), mesh(), shaderProgram(nullptr) {
        mesh.Vertices = std::vector<Vector>({
                                                    {0.0f, 0.0f, 0.0f},
                                                    {1.0f, 0.0f, 0.0f},
                                                    {0.5f, 0.5f, 0.0f},
                                                    {1.0f, 0.0f, 0.0f},
                                                    {1.5f, 0.5f, 0.0f},
                                                    {0.5f, 0.5f, 0.0f}
                                            });
    }

    Parallelogram::Parallelogram(GLfloat RGBA[6][4]) : Parallelogram() {
        for (int i = 0; i < 6; ++i) {
            mesh.Colors.emplace_back(RGBA[i][0], RGBA[i][1], RGBA[i][2],
                                     RGBA[i][3]);
        }
    }

    Parallelogram::~Parallelogram() = default;

    void Parallelogram::Init() {
        if (!shaderProgram) {
            shaderProgram = std::make_shared<ShaderProgram>(
                    "shaders/SimpleColor/program.json");
        }
        shaderProgram->Init();
        mesh.Init();

    }

    void Parallelogram::Draw() {
        mesh.Bind();
        shaderProgram->Bind();

        number matrixArray[16];
        transform.ToArray(matrixArray);
        glUniformMatrix4fv(shaderProgram->GetUniformLocationId("Matrix"), 1,
                           GL_FALSE, matrixArray);
        mesh.Draw();

        shaderProgram->Unbind();
        mesh.Unbind();

        CheckOpenGLError("Could not draw Actor.");
    }

} /* namespace Divisaction */