/*
 * File Cube.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "Cube.h"

#define VERTICES 0
#define COLORS 1

namespace ThreeEngine {

    Cube::Cube() : IDrawable(), mesh(), shaderProgram(nullptr), color{.1f, .5f, .1f, 1.0f} {
        mesh.Vertices = std::vector<Vector>({
                                               {0.0f, 0.0f, 1.0f}, // 0 - FRONT
                                               {1.0f, 0.0f, 1.0f}, // 1
                                               {1.0f, 1.0f, 1.0f}, // 2
                                               {1.0f, 1.0f, 1.0f}, // 2
                                               {0.0f, 1.0f, 1.0f}, // 3
                                               {0.0f, 0.0f, 1.0f}, // 0

                                               {1.0f, 0.0f, 1.0f}, // 1 - RIGHT
                                               {1.0f, 0.0f, 0.0f}, // 5
                                               {1.0f, 1.0f, 0.0f}, // 6
                                               {1.0f, 1.0f, 0.0f}, // 6
                                               {1.0f, 1.0f, 1.0f}, // 2
                                               {1.0f, 0.0f, 1.0f}, // 1

                                               {1.0f, 1.0f, 1.0f}, // 2 - TOP
                                               {1.0f, 1.0f, 0.0f}, // 6
                                               {0.0f, 1.0f, 0.0f}, // 7
                                               {0.0f, 1.0f, 0.0f}, // 7
                                               {0.0f, 1.0f, 1.0f}, // 3
                                               {1.0f, 1.0f, 1.0f}, // 2

                                               {1.0f, 0.0f, 0.0f}, // 5 - BACK
                                               {0.0f, 0.0f, 0.0f}, // 4
                                               {0.0f, 1.0f, 0.0f}, // 7
                                               {0.0f, 1.0f, 0.0f}, // 7
                                               {1.0f, 1.0f, 0.0f}, // 6
                                               {1.0f, 0.0f, 0.0f}, // 5

                                               {0.0f, 0.0f, 0.0f}, // 4 - LEFT
                                               {0.0f, 0.0f, 1.0f}, // 0
                                               {0.0f, 1.0f, 1.0f}, // 3
                                               {0.0f, 1.0f, 1.0f}, // 3
                                               {0.0f, 1.0f, 0.0f}, // 7
                                               {0.0f, 0.0f, 0.0f}, // 4

                                               {0.0f, 0.0f, 1.0f}, // 0 - BOTTOM
                                               {0.0f, 0.0f, 0.0f}, // 4
                                               {1.0f, 0.0f, 0.0f}, // 5
                                               {1.0f, 0.0f, 0.0f}, // 5
                                               {1.0f, 0.0f, 1.0f}, // 1
                                               {0.0f, 0.0f, 1.0f}  // 0
                                       });
    }

    Cube::~Cube() = default;

    void Cube::Init() {
        if (!shaderProgram) {
            shaderProgram = std::make_shared<ShaderProgram>(
                    "shaders/Color3D/program.json");
        }
        shaderProgram->Init();
        mesh.Init();
    }

    void Cube::Draw() {
        mesh.Bind();
        shaderProgram->Bind();

        number matrixArray[16];
        transform.ToArray(matrixArray);
        glUniformMatrix4fv(shaderProgram->GetUniformLocationId("ModelMatrix"),
                           1, GL_FALSE,
                           matrixArray);
        glUniform4f(shaderProgram->GetUniformLocationId("ModelColor"), color[0],
                    color[1], color[2],
                    color[3]);
        //glUniform4fv(shaderProgram->GetUniformLocationId("ModelColor"), 4, color);
        mesh.Draw();

        shaderProgram->Unbind();
        mesh.Unbind();

        CheckOpenGLError("Could not draw Actor.");
    }

} /* namespace Divisaction */