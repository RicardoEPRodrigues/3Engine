/*
 * File Tangram.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "Quaternion.h"
#include "Engine/Camera/Perspective.h"
#include "Engine/Camera/LookAt.h"
#include "Engine/Shapes/Triangle3D.h"
#include "Engine/Shapes/Cube.h"
#include "Engine/Shapes/Parallelogram3D.h"

#define VERTICES 0
#define COLORS 1

using json = nlohmann::json;

namespace ThreeEngine {


    Quaternion::Quaternion() : Engine(), shapeToShow(CUBE), controller() { }

    Quaternion::~Quaternion() = default;

    void Quaternion::OnInit() {
        switch (shapeToShow) {
            case CUBE:
                CubeScene();
                break;
        }
    }

    void Quaternion::CubeScene() {
        auto colorProgram = std::make_shared<ShaderProgram>("shaders/Color3D/program.json");
        colorProgram->Init();

        Debug::Log(*colorProgram);

        { // Camera handling
            delete camera;

            number width = config["window"]["x"];
            number height = config["window"]["y"];
            number aspect = width / height;
            camera = new Camera(
                    static_cast<GLuint>(colorProgram->GetUniformBlockBidingId("SharedMatrices")),
                    new Perspective(30, aspect, 1, 100),
                    new Matrix(Matrix::TranslationMatrix(Vector(0, 0, -10)))
//                    new LookAt({5, 0.5f, 0}, {0, 0.5f, 0}, {0, 1, 0})
            );
        }

        float triangleSize = 0.7071f;

        { // Big triangle to the Left
            auto* triangle = new Triangle3D();
            Matrix2 transform2D =
                    (TMatrix<2, 2>) Matrix2::RotationMatrix(135) *
                    Matrix2::ScaleMatrix(triangleSize * 2, triangleSize * 2);
            triangle->transform =
                    Matrix::TranslationMatrix({0.0f, 0.0f, 0, 0}) *
                    Matrix(transform2D);
            actors.push_back((IActor*) triangle);

            triangle->shaderProgram = colorProgram;
            triangle->color[0] = .5f;
        }
        { // Big triangle to the Top
            auto* triangle = new Triangle3D();
            Matrix2 transform2D =
                    (TMatrix<2, 2>) Matrix2::RotationMatrix(45) *
                    Matrix2::ScaleMatrix(triangleSize * 2, triangleSize * 2);
            triangle->transform = Matrix::TranslationMatrix({0.0f, 0.0f, .5f, 0}) *
                                  Matrix(transform2D);
            actors.push_back((IActor*) triangle);

            triangle->shaderProgram = colorProgram;
            triangle->color[1] = .5f;
        }
        { // Small triangle at the center
            auto* triangle = new Triangle3D();
            Matrix2 transform2D = (TMatrix<2, 2>) Matrix2::RotationMatrix(-135) *
                                  Matrix2::ScaleMatrix(triangleSize, triangleSize);
            triangle->transform =
                    Matrix::TranslationMatrix({0.0f, 0.0f, -.5f, 0}) * Matrix(transform2D);
            actors.push_back((IActor*) triangle);

            triangle->shaderProgram = colorProgram;
        }
        { // Small triangle at the top right
            auto* triangle = new Triangle3D();
            Matrix2 transform2D = (TMatrix<2, 2>) Matrix2::RotationMatrix(-45) *
                                  Matrix2::ScaleMatrix(triangleSize, triangleSize);
            triangle->transform =
                    Matrix::TranslationMatrix({0.5f, 0.5f, 0.2f, 0}) *
                    Matrix(transform2D);
            actors.push_back((IActor*) triangle);

            triangle->shaderProgram = colorProgram;
            triangle->color[0] = .5f;
            triangle->color[1] = .5f;
        }
        { // Medium triangle to the bottom right
            auto* triangle = new Triangle3D();
            Matrix2 transform2D =
                    (TMatrix<2, 2>) Matrix2::RotationMatrix(90);
            triangle->transform =
                    Matrix::TranslationMatrix({1.0f, -1.0f, -0.2f, 0}) * Matrix(transform2D);
            actors.push_back((IActor*) triangle);

            triangle->shaderProgram = colorProgram;
            triangle->color[0] = .2f;
            triangle->color[1] = .7f;
        }
        { // Square
            auto* square = new Cube();
            Matrix2 transform2D =
                    (TMatrix<2, 2>) Matrix2::RotationMatrix(-45) *
                    Matrix2::ScaleMatrix(triangleSize, triangleSize);
            square->transform = Matrix(transform2D);
            actors.push_back((IActor*) square);

            square->shaderProgram = colorProgram;
        }
        { // Parallelogram
            auto* parallelogram = new Parallelogram3D();
            parallelogram->transform =
                    Matrix::TranslationMatrix({0.0f, 0.0f, -1, 0}) *
                    Matrix::TranslationMatrix(Vector({-1, -1, 0}));
            actors.push_back((IActor*) parallelogram);

            parallelogram->shaderProgram = colorProgram;
        }

    }

    void Quaternion::OnReshape(int, int) {
//        number aspect = (number) w / (number) h,
//                angle = Maths::ToRadians(30.0f / 2.0f),
//                d = 1.0f / tanf(angle);
//        camera->projection.M[0][0] = d / aspect;
    }

    void Quaternion::PreDraw() {
        if (input.Click(27)) {
            Exit();
        }
        controller.Update();
    }

} /* namespace Divisaction */