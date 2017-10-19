/*
 * File Tangram.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include <GL/glew.h>
#include "Tangram.h"
#include "../Math/Matrix.h"
#include "Triangle.h"
#include "Square.h"
#include "Parallelogram.h"
#include "../Debug.h"

#define VERTICES 0
#define COLORS 1

GLuint VaoId, VboId[2];
GLint UniformId;

using json = nlohmann::json;

namespace ThreeEngine {


    Tangram::Tangram() : Engine() {
    }

    Tangram::~Tangram() = default;

    void Tangram::OnInit() {
        SimpleTangram();

        for (auto it = actors.begin(); it != actors.end(); ++it) {
            (*it)->Init();
        }
    }

    void Tangram::SimpleTangram() {
        auto colorProgram = std::make_shared<ShaderProgram>("shaders/Tangram.json");
        colorProgram->Init();
        auto wireframeProgram = std::make_shared<ShaderProgram>("shaders/Wireframe.json");
        wireframeProgram->Init();
        Debug::Log(*colorProgram);
        Debug::Log(*wireframeProgram);

        { // Big triangle to the Left
            auto* triangle = new Triangle();
            Matrix2 transform2D =
                    (TMatrix<2, 2>) Matrix2::RotationMatrix(135) * Matrix2::ScaleMatrix(2, 2);
            triangle->transform =
                    Matrix::TranslationMatrix({0.0f, 0.0f, 0, 0}) * Matrix(transform2D);
            actors.push_back((IActor*) triangle);

            triangle->shaderProgram = wireframeProgram;
        }
        { // Big triangle to the Top
            Triangle::Vertex vertices[3] = {
                    {{0.0f,    0.0f,    0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
                    {{0.7071f, 0.0f,    0.0f, 1.0f}, {1.0f, 1.0f, 0.0f, 1.0f}},
                    {{0.0f,    0.7071f, 0.0f, 1.0f}, {1.0f, 0.0f, 1.0f, 1.0f}}
            };
            auto* triangle = new Triangle(vertices);
            Matrix2 transform2D =
                    (TMatrix<2, 2>) Matrix2::RotationMatrix(45) * Matrix2::ScaleMatrix(2, 2);
            triangle->transform =
                    Matrix::TranslationMatrix({0.0f, 0.0f, 0, 0}) * Matrix(transform2D);
            actors.push_back((IActor*) triangle);

            triangle->shaderProgram = colorProgram;
        }
        { // Small triangle at the center
            Triangle::Vertex vertices[3] = {
                    {{0.0f,    0.0f,    0.0f, 1.0f}, {1.0f, 0.0f, 1.0f, 1.0f}},
                    {{0.7071f, 0.0f,    0.0f, 1.0f}, {0.0f, 1.0f, 1.0f, 1.0f}},
                    {{0.0f,    0.7071f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}}
            };
            auto* triangle = new Triangle(vertices);
            Matrix2 transform2D = (TMatrix<2, 2>) Matrix2::RotationMatrix(-135);
            triangle->transform = Matrix(transform2D);
            actors.push_back((IActor*) triangle);

            triangle->shaderProgram = colorProgram;
        }
        { // Small triangle at the top right
            auto* triangle = new Triangle();
            Matrix2 transform2D = (TMatrix<2, 2>) Matrix2::RotationMatrix(-45);
            triangle->transform =
                    Matrix::TranslationMatrix({0.5f, 0.5f, 0, 0}) *
                    Matrix(transform2D);
            actors.push_back((IActor*) triangle);

            triangle->shaderProgram = wireframeProgram;
        }
        { // Medium triangle to the bottom right
            auto* triangle = new Triangle();
            Matrix2 transform2D =
                    (TMatrix<2, 2>) Matrix2::RotationMatrix(90) * Matrix2::ScaleMatrix(1.414f, 1.414f);
            triangle->transform =
                    Matrix::TranslationMatrix({1.0f, -1.0f, 0, 0}) * Matrix(transform2D);
            actors.push_back((IActor*) triangle);

            triangle->shaderProgram = colorProgram;
        }
        { // Square
            auto* square = new Square();
            Matrix2 transform2D =
                    (TMatrix<2, 2>) Matrix2::RotationMatrix(-45);
            square->transform = Matrix(transform2D);
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

    void Tangram::OnCleanup() {
        for (auto& actor : actors) {
            delete actor;
        }
    }

    void Tangram::DrawScene() {
        for (auto& actor : actors) {
            actor->Draw();
        }
    }

} /* namespace Divisaction */