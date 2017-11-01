/*
 * File Tangram.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include <GL/glew.h>
#include "Tangram.h"
#include "Engine/Shapes/Triangle.h"
#include "Engine/Shapes/Square.h"
#include "Engine/Shapes/Parallelogram.h"

#define VERTICES 0
#define COLORS 1

using json = nlohmann::json;

namespace ThreeEngine {


    Tangram::Tangram() : Engine(), shapeToShow(FISH) {}

    Tangram::~Tangram() = default;

    void Tangram::OnInit() {
        switch (shapeToShow) {
            case SAMPLE:
                Shapes();
                break;
            case TANGRAM:
                SimpleTangram();
                break;
            case HEART:
                Heart();
                break;
            case FISH:
                Fish();
                break;
        }
    }

    void Tangram::Shapes() {
        auto colorProgram = std::make_shared<ShaderProgram>("shaders/SimpleColor/program.json");
        colorProgram->Init();
        auto wireframeProgram = std::make_shared<ShaderProgram>("shaders/Wireframe/program.json");
        wireframeProgram->Init();

        Debug::Log(*colorProgram);
        Debug::Log(*wireframeProgram);

        { // Small triangle at the top right
            auto* triangle = new Triangle();
            triangle->transform = Matrix::TranslationMatrix({0.2f, 0.2f, 0, 0});
            actors.push_back((IActor*) triangle);

            triangle->shaderProgram = wireframeProgram;
        }
        { // Square
            GLfloat RGBA[6][4] = {
                    {1.0f, 0.0f, 0.0f, 1.0f},
                    {0.5f, 0.1f, 0.8f, 1.0f},
                    {0.0f, 0.0f, 1.0f, 1.0f},
                    {0.5f, 0.1f, 0.8f, 1.0f},
                    {0.3f, 0.1f, 0.8f, 1.0f},
                    {0.0f, 0.0f, 1.0f, 1.0f}
            };
            auto* square = new Square(RGBA);
            square->transform = Matrix::TranslationMatrix({-0.8f, 0, 0, 0});
            actors.push_back((IActor*) square);

            square->shaderProgram = colorProgram;
        }
        { // Parallelogram
            auto* parallelogram = new Parallelogram();
            parallelogram->transform = Matrix::TranslationMatrix(Vector({-1, -1, 0}));
            actors.push_back((IActor*) parallelogram);

            parallelogram->shaderProgram = colorProgram;
        }
    }

    void Tangram::SimpleTangram() {
        auto colorProgram = std::make_shared<ShaderProgram>("shaders/SimpleColor/program.json");
        colorProgram->Init();
        auto wireframeProgram = std::make_shared<ShaderProgram>("shaders/Wireframe/program.json");
        wireframeProgram->Init();
        Debug::Log(*colorProgram);
        Debug::Log(*wireframeProgram);

        Matrix viewM = Matrix::IdentityMatrix();

        { // Big triangle to the Left
            auto* triangle = new Triangle();
            Matrix2 transform2D =
                    (TMatrix<2, 2>) Matrix2::RotationMatrix(135) * Matrix2::ScaleMatrix(2, 2);
            triangle->transform = viewM *
                                  Matrix::TranslationMatrix({0.0f, 0.0f, 0, 0}) *
                                  Matrix(transform2D);
            actors.push_back((IActor*) triangle);

            triangle->shaderProgram = wireframeProgram;
        }
        { // Big triangle to the Top
            GLfloat RGBA[3][4] = {
                    {1.0f, 0.0f, 0.0f, 1.0f},
                    {1.0f, 1.0f, 0.0f, 1.0f},
                    {1.0f, 0.0f, 1.0f, 1.0f}
            };
            auto* triangle = new Triangle(RGBA);
            Matrix2 transform2D =
                    (TMatrix<2, 2>) Matrix2::RotationMatrix(45) * Matrix2::ScaleMatrix(2, 2);
            triangle->transform = viewM *
                                  Matrix::TranslationMatrix({0.0f, 0.0f, 0, 0}) *
                                  Matrix(transform2D);
            actors.push_back((IActor*) triangle);

            triangle->shaderProgram = colorProgram;
        }
        { // Small triangle at the center
            GLfloat RGBA[3][4] = {
                    {1.0f, 0.0f, 1.0f, 1.0f},
                    {0.0f, 1.0f, 1.0f, 1.0f},
                    {0.0f, 0.0f, 1.0f, 1.0f}
            };
            auto* triangle = new Triangle(RGBA);
            Matrix2 transform2D = (TMatrix<2, 2>) Matrix2::RotationMatrix(-135);
            triangle->transform = viewM * Matrix(transform2D);
            actors.push_back((IActor*) triangle);

            triangle->shaderProgram = colorProgram;
        }
        { // Small triangle at the top right
            auto* triangle = new Triangle();
            Matrix2 transform2D = (TMatrix<2, 2>) Matrix2::RotationMatrix(-45);
            triangle->transform =
                    viewM * Matrix::TranslationMatrix({0.5f, 0.5f, 0, 0}) *
                    Matrix(transform2D);
            actors.push_back((IActor*) triangle);

            triangle->shaderProgram = wireframeProgram;
        }
        { // Medium triangle to the bottom right
            auto* triangle = new Triangle();
            Matrix2 transform2D =
                    (TMatrix<2, 2>) Matrix2::RotationMatrix(90) *
                    Matrix2::ScaleMatrix(1.414f, 1.414f);
            triangle->transform =
                    viewM * Matrix::TranslationMatrix({1.0f, -1.0f, 0, 0}) * Matrix(transform2D);
            actors.push_back((IActor*) triangle);

            triangle->shaderProgram = colorProgram;
        }
        { // Square
            GLfloat RGBA[6][4] = {
                    {1.0f, 0.0f, 0.0f, 1.0f},
                    {0.5f, 0.1f, 0.8f, 1.0f},
                    {0.0f, 0.0f, 1.0f, 1.0f},
                    {0.5f, 0.1f, 0.8f, 1.0f},
                    {0.3f, 0.1f, 0.8f, 1.0f},
                    {0.0f, 0.0f, 1.0f, 1.0f}
            };
            auto* square = new Square(RGBA);
            Matrix2 transform2D =
                    (TMatrix<2, 2>) Matrix2::RotationMatrix(-45);
            square->transform = viewM * Matrix(transform2D);
            actors.push_back((IActor*) square);

            square->shaderProgram = colorProgram;
        }
        { // Parallelogram
            auto* parallelogram = new Parallelogram();
            parallelogram->transform = viewM * Matrix::TranslationMatrix(Vector({-1, -1, 0}));
            actors.push_back((IActor*) parallelogram);

            parallelogram->shaderProgram = colorProgram;
        }
    }

    void Tangram::Heart() {
        // Backface culling with front face detected using Counter Clockwise hand
        glDisable(GL_CULL_FACE);

        auto colorProgram = std::make_shared<ShaderProgram>("shaders/SimpleColor/program.json");
        colorProgram->Init();
        auto wireframeProgram = std::make_shared<ShaderProgram>("shaders/Wireframe/program.json");
        wireframeProgram->Init();
        Debug::Log(*colorProgram);
        Debug::Log(*wireframeProgram);

        Matrix viewM = Matrix(Matrix2::ScaleMatrix(.6f, .6f));

        { // Big triangle to the Left
            auto* triangle = new Triangle();
            Matrix2 transform2D =
                    (TMatrix<2, 2>) Matrix2::RotationMatrix(-135) * Matrix2::ScaleMatrix(2, 2);
            triangle->transform = viewM *
                                  Matrix::TranslationMatrix({-.5f, 1.0f, 0, 0}) *
                                  Matrix(transform2D);
            actors.push_back((IActor*) triangle);

            triangle->shaderProgram = wireframeProgram;
        }
        { // Parallelogram
            auto* parallelogram = new Parallelogram();
            Matrix2 transform2D =
                    (TMatrix<2, 2>) Matrix2::ScaleMatrix(-1, 1);
            parallelogram->transform =
                    viewM * Matrix::TranslationMatrix(Vector({1.5, 0, 0})) * Matrix(transform2D);
            actors.push_back((IActor*) parallelogram);

            parallelogram->shaderProgram = colorProgram;
        }
        { // Small triangle at the top right
            auto* triangle = new Triangle();
            Matrix2 transform2D = (TMatrix<2, 2>) Matrix2::RotationMatrix(-135);
            triangle->transform =
                    viewM * Matrix::TranslationMatrix({0.5f, 1, 0, 0}) *
                    Matrix(transform2D);
            actors.push_back((IActor*) triangle);

            triangle->shaderProgram = wireframeProgram;
        }
        { // Medium triangle
            auto* triangle = new Triangle();
            Matrix2 transform2D =
                    (TMatrix<2, 2>) Matrix2::RotationMatrix(180) *
                    Matrix2::ScaleMatrix(1.414f, 1.414f);
            triangle->transform =
                    viewM * Matrix::TranslationMatrix({-0.5f, 0, 0, 0}) * Matrix(transform2D);
            actors.push_back((IActor*) triangle);

            triangle->shaderProgram = colorProgram;
        }
        { // Small triangle at the center
            GLfloat RGBA[3][4] = {
                    {1.0f, 0.0f, 1.0f, 1.0f},
                    {0.0f, 1.0f, 1.0f, 1.0f},
                    {0.0f, 0.0f, 1.0f, 1.0f}
            };
            auto* triangle = new Triangle(RGBA);
            Matrix2 transform2D = (TMatrix<2, 2>) Matrix2::RotationMatrix(135);
            triangle->transform =
                    viewM * Matrix::TranslationMatrix({0, -.5f, 0, 0}) * Matrix(transform2D);
            actors.push_back((IActor*) triangle);

            triangle->shaderProgram = colorProgram;
        }
        { // Big triangle to the Top
            GLfloat RGBA[3][4] = {
                    {1.0f, 0.0f, 0.0f, 1.0f},
                    {1.0f, 1.0f, 0.0f, 1.0f},
                    {1.0f, 0.0f, 1.0f, 1.0f}
            };
            auto* triangle = new Triangle(RGBA);
            Matrix2 transform2D =
                    (TMatrix<2, 2>) Matrix2::RotationMatrix(45) * Matrix2::ScaleMatrix(2, 2);
            triangle->transform =
                    viewM * Matrix::TranslationMatrix({0.5f, -1.0f, 0, 0}) * Matrix(transform2D);
            actors.push_back((IActor*) triangle);

            triangle->shaderProgram = colorProgram;
        }
        { // Square
            GLfloat RGBA[6][4] = {
                    {1.0f, 0.0f, 0.0f, 1.0f},
                    {0.5f, 0.1f, 0.8f, 1.0f},
                    {0.0f, 0.0f, 1.0f, 1.0f},
                    {0.5f, 0.1f, 0.8f, 1.0f},
                    {0.3f, 0.1f, 0.8f, 1.0f},
                    {0.0f, 0.0f, 1.0f, 1.0f}
            };
            auto* square = new Square(RGBA);
            Matrix2 transform2D =
                    (TMatrix<2, 2>) Matrix2::RotationMatrix(-45);
            square->transform =
                    viewM * Matrix::TranslationMatrix({-0.5f, -1.0f, 0, 0}) * Matrix(transform2D);
            actors.push_back((IActor*) square);

            square->shaderProgram = wireframeProgram;
        }
    }

    void Tangram::Fish() {
        // Backface culling with front face detected using Counter Clockwise hand
        glDisable(GL_CULL_FACE);

        auto colorProgram = std::make_shared<ShaderProgram>("shaders/SimpleColor/program.json");
        colorProgram->Init();
        auto wireframeProgram = std::make_shared<ShaderProgram>("shaders/Wireframe/program.json");
        wireframeProgram->Init();
        Debug::Log(*colorProgram);
        Debug::Log(*wireframeProgram);

        Matrix viewM = Matrix(Matrix2::ScaleMatrix(.6f, .6f));

        { // Medium triangle
            auto* triangle = new Triangle();
            Matrix2 transform2D =
                    (TMatrix<2, 2>) Matrix2::RotationMatrix(-45) *
                    Matrix2::ScaleMatrix(1.414f, 1.414f);
            triangle->transform =
                    viewM * Matrix::TranslationMatrix({-1.5f, 0, 0, 0}) * Matrix(transform2D);
            actors.push_back((IActor*) triangle);

            triangle->shaderProgram = colorProgram;
        }
        { // Big triangle to the Left
            auto* triangle = new Triangle();
            Matrix2 transform2D =
                    (TMatrix<2, 2>) Matrix2::RotationMatrix(-90) * Matrix2::ScaleMatrix(2, 2);
            triangle->transform =
                    viewM * Matrix::TranslationMatrix({-.8f, .7071f * 2, 0, 0}) *
                    Matrix(transform2D);
            actors.push_back((IActor*) triangle);

            triangle->shaderProgram = wireframeProgram;
        }
        { // Big triangle to the Top
            GLfloat RGBA[3][4] = {
                    {1.0f, 0.0f, 0.0f, 1.0f},
                    {1.0f, 1.0f, 0.0f, 1.0f},
                    {1.0f, 0.0f, 1.0f, 1.0f}
            };
            auto* triangle = new Triangle(RGBA);
            Matrix2 transform2D =
                    (TMatrix<2, 2>) Matrix2::ScaleMatrix(2, 2);
            triangle->transform =
                    viewM * Matrix::TranslationMatrix({-.8f, -.7071f * 2, 0, 0}) *
                    Matrix(transform2D);
            actors.push_back((IActor*) triangle);

            triangle->shaderProgram = colorProgram;
        }
        { // Square
            GLfloat RGBA[6][4] = {
                    {1.0f, 0.0f, 0.0f, 1.0f},
                    {0.5f, 0.1f, 0.8f, 1.0f},
                    {0.0f, 0.0f, 1.0f, 1.0f},
                    {0.5f, 0.1f, 0.8f, 1.0f},
                    {0.3f, 0.1f, 0.8f, 1.0f},
                    {0.0f, 0.0f, 1.0f, 1.0f}
            };
            auto* square = new Square(RGBA);
            Matrix2 transform2D =
                    (TMatrix<2, 2>) Matrix2::RotationMatrix(-45);
            square->transform =
                    viewM * Matrix::TranslationMatrix({-0.8f, 0.0f, 0, 0}) * Matrix(transform2D);
            actors.push_back((IActor*) square);

            square->shaderProgram = colorProgram;
        }
        { // Parallelogram
            auto* parallelogram = new Parallelogram();
            Matrix2 transform2D =
                    (TMatrix<2, 2>) Matrix2::RotationMatrix(-135) * Matrix2::ScaleMatrix(-1, 1);
            parallelogram->transform =
                    viewM * Matrix::TranslationMatrix(Vector({.2f, 0, 0})) * Matrix(transform2D);
            actors.push_back((IActor*) parallelogram);

            parallelogram->shaderProgram = colorProgram;
        }
        { // Small triangle at the top right
            auto* triangle = new Triangle();
            Matrix2 transform2D = (TMatrix<2, 2>) Matrix2::RotationMatrix(180);
            triangle->transform =
                    viewM * Matrix::TranslationMatrix({0.7071f + .2f, 0, 0, 0}) *
                    Matrix(transform2D);
            actors.push_back((IActor*) triangle);

            triangle->shaderProgram = wireframeProgram;
        }
        { // Small triangle at the center
            GLfloat RGBA[3][4] = {
                    {1.0f, 0.0f, 1.0f, 1.0f},
                    {0.0f, 1.0f, 1.0f, 1.0f},
                    {0.0f, 0.0f, 1.0f, 1.0f}
            };
            auto* triangle = new Triangle(RGBA);
            triangle->transform =
                    viewM * Matrix::TranslationMatrix({0.7071f + .2f, -.7071f, 0, 0});
            actors.push_back((IActor*) triangle);

            triangle->shaderProgram = colorProgram;
        }
    }

} /* namespace Divisaction */