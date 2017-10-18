/*
 * File Tangram.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include <GL/glew.h>
#include "Tangram.h"
#include "../Math/Matrix.h"
#include "Triangle.h"

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


        { // Big triangle to the Left
            auto* triangle = new Triangle();
            Matrix2 transform2D =
                    (TMatrix<2, 2>) Matrix2::RotationMatrix(135) * Matrix2::ScaleMatrix(4, 4);
            triangle->transform =
                    Matrix::TranslationMatrix({0.0f, 0.0f, 0, 0}) * Matrix(transform2D);
            actors.push_back((IActor*) triangle);

            triangle->shaderProgram = ShaderProgram::LoadJsonFile("shaders/Wireframe.json");
        }
        { // Big triangle to the Top
            Triangle::Vertex vertices[3] = {
                    {{0.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
                    {{0.3536f, 0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 0.0f, 1.0f}},
                    {{0.0f, 0.3536f, 0.0f, 1.0f}, {1.0f, 0.0f, 1.0f, 1.0f}}
            };
            auto* triangle = new Triangle(vertices);
            Matrix2 transform2D =
                    (TMatrix<2, 2>) Matrix2::RotationMatrix(45) * Matrix2::ScaleMatrix(4, 4);
            triangle->transform =
                    Matrix::TranslationMatrix({0.0f, 0.0f, 0, 0}) * Matrix(transform2D);
            actors.push_back((IActor*) triangle);
        }
        { // Small triangle at the center
            Triangle::Vertex vertices[3] = {
                    {{0.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 1.0f, 1.0f}},
                    {{0.3536f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f, 1.0f}},
                    {{0.0f, 0.3536f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}}
            };
            auto* triangle = new Triangle(vertices);
            Matrix2 transform2D = (TMatrix<2, 2>) Matrix2::RotationMatrix(-135) * Matrix2::ScaleMatrix(1.9f, 1.9f);
            triangle->transform = Matrix(transform2D);
            actors.push_back((IActor*) triangle);
        }
        { // Small triangle at the top right
            auto* triangle = new Triangle();
            Matrix2 transform2D = (TMatrix<2, 2>) Matrix2::RotationMatrix(-45) * Matrix2::ScaleMatrix(1.9f, 1.9f);
            triangle->transform =
                    Matrix::TranslationMatrix({0.525f, 0.525f, 0, 0}) *
                    Matrix(transform2D);
            actors.push_back((IActor*) triangle);

            triangle->shaderProgram = ShaderProgram::LoadJsonFile("shaders/Wireframe.json");
        }
        { // Medium triangle to the bottom right
            auto* triangle = new Triangle();
            Matrix2 transform2D =
                    (TMatrix<2, 2>) Matrix2::RotationMatrix(90) * Matrix2::ScaleMatrix(3, 3);
            triangle->transform =
                    Matrix::TranslationMatrix({1.0f, -1.0f, 0, 0}) * Matrix(transform2D);
            actors.push_back((IActor*) triangle);
        }

        for (auto it = actors.begin(); it != actors.end(); ++it) {
            (*it)->Init();
        }
    }

    void Tangram::OnCleanup() {
        for (auto it = actors.begin(); it != actors.end(); ++it) {
            delete *it;
        }
    }

    void Tangram::DrawScene() {
        for (auto it = actors.begin(); it != actors.end(); ++it) {
            (*it)->Draw();
        }
    }

} /* namespace Divisaction */