/*
 * File BasicShapes.cpp in project 3EngineGlobal
 * 
 * Copyright (C) Ricardo Rodrigues 2018 - All Rights Reserved
 */
#include "BasicShapes.h"

namespace ThreeEngine {

    BasicShapes::BasicShapes() = default;

    std::shared_ptr<Mesh> BasicShapes::Triangle(float width) {
        auto mesh = std::make_shared<Mesh>();
        mesh->Vertices = std::vector<Vector>({
                                                     {0.0f,  0.0f,  0.0f},
                                                     {width, 0.0f,  0.0f},
                                                     {0.0f,  width, 0.0f}
                                             });
        for (Vector& v : mesh->Vertices) {
            v.X -= width * 0.5f;
            v.Y -= width * 0.5f;
        }
        return mesh;
    }

    std::shared_ptr<Mesh> BasicShapes::Square(float width) {
        auto mesh = std::make_shared<Mesh>();
        mesh->Vertices = std::vector<Vector>({
                                                     {0.0f,  0.0f,  0.0f},
                                                     {width, 0.0f,  0.0f},
                                                     {0.0f,  width, 0.0f},
                                                     {width, 0.0f,  0.0f},
                                                     {width, width, 0.0f},
                                                     {0.0f,  width, 0.0f}
                                             });
        for (Vector& v : mesh->Vertices) {
            v.X -= width * 0.5f;
            v.Y -= width * 0.5f;
        }
        return mesh;
    }

    std::shared_ptr<Mesh> BasicShapes::Parallelogram(float width) {
        auto mesh = std::make_shared<Mesh>();
        float one_third = width / 3.0f, two_thirds = one_third * 2;
        mesh->Vertices = std::vector<Vector>({
                                                     {0.0f,       0.0f,      0}, // 0 - FRONT
                                                     {two_thirds, 0.0f,      0}, // 1
                                                     {width,      one_third, 0}, // 2
                                                     {width,      one_third, 0}, // 2
                                                     {one_third,  one_third, 0}, // 3
                                                     {0.0f,       0.0f,      0}, // 0
                                             });
        return mesh;
    }

    std::shared_ptr<Mesh> BasicShapes::Cube(float width) {
        auto mesh = std::make_shared<Mesh>();
        mesh->Vertices = std::vector<Vector>({
                                                     {0.0f,  0.0f,  width}, // 0 - FRONT
                                                     {width, 0.0f,  width}, // 1
                                                     {width, width, width}, // 2
                                                     {width, width, width}, // 2
                                                     {0.0f,  width, width}, // 3
                                                     {0.0f,  0.0f,  width}, // 0

                                                     {width, 0.0f,  width}, // 1 - RIGHT
                                                     {width, 0.0f,  0.0f}, // 5
                                                     {width, width, 0.0f}, // 6
                                                     {width, width, 0.0f}, // 6
                                                     {width, width, width}, // 2
                                                     {width, 0.0f,  width}, // 1

                                                     {width, width, width}, // 2 - TOP
                                                     {width, width, 0.0f}, // 6
                                                     {0.0f,  width, 0.0f}, // 7
                                                     {0.0f,  width, 0.0f}, // 7
                                                     {0.0f,  width, width}, // 3
                                                     {width, width, width}, // 2

                                                     {width, 0.0f,  0.0f}, // 5 - BACK
                                                     {0.0f,  0.0f,  0.0f}, // 4
                                                     {0.0f,  width, 0.0f}, // 7
                                                     {0.0f,  width, 0.0f}, // 7
                                                     {width, width, 0.0f}, // 6
                                                     {width, 0.0f,  0.0f}, // 5

                                                     {0.0f,  0.0f,  0.0f}, // 4 - LEFT
                                                     {0.0f,  0.0f,  width}, // 0
                                                     {0.0f,  width, width}, // 3
                                                     {0.0f,  width, width}, // 3
                                                     {0.0f,  width, 0.0f}, // 7
                                                     {0.0f,  0.0f,  0.0f}, // 4

                                                     {0.0f,  0.0f,  width}, // 0 - BOTTOM
                                                     {0.0f,  0.0f,  0.0f}, // 4
                                                     {width, 0.0f,  0.0f}, // 5
                                                     {width, 0.0f,  0.0f}, // 5
                                                     {width, 0.0f,  width}, // 1
                                                     {0.0f,  0.0f,  width}  // 0
                                             });
        for (Vector& v : mesh->Vertices) {
            v -= width * 0.5f;
        }
        return mesh;
    }

    std::shared_ptr<Mesh> BasicShapes::TriangularParallelepiped(float width) {
        auto mesh = std::make_shared<Mesh>();
        mesh->Vertices = std::vector<Vector>({
                                                     {0.0f,  0.0f,  width}, // 0 - FRONT
                                                     {width, 0.0f,  width}, // 1
                                                     {0.0f,  width, width}, // 2

                                                     {width, 0.0f,  width}, // 1 - RIGHT
                                                     {width, 0.0f,  0.0f}, // 5
                                                     {0.0f,  width, 0.0f}, // 6
                                                     {0.0f,  width, 0.0f}, // 6
                                                     {0.0f,  width, width}, // 2
                                                     {width, 0.0f,  width}, // 1

                                                     {width, 0.0f,  0.0f}, // 5 - BACK
                                                     {0.0f,  0.0f,  0.0f}, // 4
                                                     {0.0f,  width, 0.0f}, // 7

                                                     {0.0f,  0.0f,  0.0f}, // 4 - LEFT
                                                     {0.0f,  0.0f,  width}, // 0
                                                     {0.0f,  width, width}, // 3
                                                     {0.0f,  width, width}, // 3
                                                     {0.0f,  width, 0.0f}, // 7
                                                     {0.0f,  0.0f,  0.0f}, // 4

                                                     {0.0f,  0.0f,  width}, // 0 - BOTTOM
                                                     {0.0f,  0.0f,  0.0f}, // 4
                                                     {width, 0.0f,  0.0f}, // 5
                                                     {width, 0.0f,  0.0f}, // 5
                                                     {width, 0.0f,  width}, // 1
                                                     {0.0f,  0.0f,  width}  // 0
                                             });
        return mesh;
    }

    std::shared_ptr<Mesh> BasicShapes::SquaredParallelepiped(float width) {
        auto mesh = std::make_shared<Mesh>();
        float one_third = width / 3.0f, two_thirds = one_third * 2;
        mesh->Vertices = std::vector<Vector>({
                                                     {0.0f,       0.0f,      two_thirds}, // 0 - FRONT
                                                     {two_thirds, 0.0f,      two_thirds}, // 1
                                                     {width,      one_third, two_thirds}, // 2
                                                     {width,      one_third, two_thirds}, // 2
                                                     {one_third,  one_third, two_thirds}, // 3
                                                     {0.0f,       0.0f,      two_thirds}, // 0

                                                     {two_thirds, 0.0f,      two_thirds}, // 1 - RIGHT
                                                     {two_thirds, 0.0f,      0.0f}, // 5
                                                     {width,      one_third, 0.0f}, // 6
                                                     {width,      one_third, 0.0f}, // 6
                                                     {width,      one_third, two_thirds}, // 2
                                                     {two_thirds, 0.0f,      two_thirds}, // 1

                                                     {width,      one_third, two_thirds}, // 2 - TOP
                                                     {width,      one_third, 0.0f}, // 6
                                                     {one_third,  one_third, 0.0f}, // 7
                                                     {one_third,  one_third, 0.0f}, // 7
                                                     {one_third,  one_third, two_thirds}, // 3
                                                     {width,      one_third, two_thirds}, // 2

                                                     {two_thirds, 0.0f,      0.0f}, // 5 - BACK
                                                     {0.0f,       0.0f,      0.0f}, // 4
                                                     {one_third,  one_third, 0.0f}, // 7
                                                     {one_third,  one_third, 0.0f}, // 7
                                                     {width,      one_third, 0.0f}, // 6
                                                     {two_thirds, 0.0f,      0.0f}, // 5

                                                     {0.0f,       0.0f,      0.0f}, // 4 - LEFT
                                                     {0.0f,       0.0f,      two_thirds}, // 0
                                                     {one_third,  one_third, two_thirds}, // 3
                                                     {one_third,  one_third, two_thirds}, // 3
                                                     {one_third,  one_third, 0.0f}, // 7
                                                     {0.0f,       0.0f,      0.0f}, // 4

                                                     {0.0f,       0.0f,      two_thirds}, // 0 - BOTTOM
                                                     {0.0f,       0.0f,      0.0f}, // 4
                                                     {two_thirds, 0.0f,      0.0f}, // 5
                                                     {two_thirds, 0.0f,      0.0f}, // 5
                                                     {two_thirds, 0.0f,      two_thirds}, // 1
                                                     {0.0f,       0.0f,      two_thirds}  // 0
                                             });
        return mesh;
    }

} /* namespace 3EngineGlobal */