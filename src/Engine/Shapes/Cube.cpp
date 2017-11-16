/*
 * File Cube.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "Cube.h"

#define VERTICES 0
#define COLORS 1

namespace ThreeEngine {

    Cube::Cube() : Actor(), color{.5f, .5f, .5f, 1.0f} {
        mesh = std::make_shared<Mesh>();
        mesh->Vertices = std::vector<Vector>({
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
        for (Vector & v : mesh->Vertices) {
            v -= 0.5f;
        }
        preDraw = std::bind(&Cube::ColorUpdate, this);
    }

    Cube::~Cube() = default;

    void Cube::ColorUpdate() {
        glUniform4f(GetShaderProgram()->GetUniformLocationId("ModelColor"), color[0],
            color[1], color[2],
            color[3]);
    }

} /* namespace Divisaction */