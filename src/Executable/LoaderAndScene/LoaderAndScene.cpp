/*
 * File Tangram.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "LoaderAndScene.h"
#include "../../Engine/Camera/Perspective.h"
#include "../../Engine/Shapes/Triangle3D.h"
#include "../../Engine/Shapes/Cube.h"
#include "../../Engine/Shapes/Parallelogram3D.h"

#define VERTICES 0
#define COLORS 1

using json = nlohmann::json;

namespace ThreeEngine {


    LoaderAndScene::LoaderAndScene()
            : Engine(), controller() { }

    LoaderAndScene::~LoaderAndScene() = default;

    void LoaderAndScene::OnInit() {
        scene();
    }

    void LoaderAndScene::scene() {
        auto colorProgram = std::make_shared<ShaderProgram>(
                "shaders/Color3D/program.json");
        colorProgram->Init();

        Debug::Log(*colorProgram);

        { // Camera handling
            delete camera;

            number width = config["window"]["x"];
            number height = config["window"]["y"];
            number aspect = width / height;
            camera = new Camera(
                    static_cast<GLuint>(colorProgram->GetUniformBlockBidingId(
                            "SharedMatrices")),
                    new Perspective(30, aspect, 1, 100),
                    new Matrix(Matrix::TranslationMatrix(Vector(0, 0, -10)))
//                    new LookAt({5, 0.5f, 0}, {0, 0.5f, 0}, {0, 1, 0})
            );
        }

        { // Square
            auto* square = new Cube();
            square->transform = Matrix::TranslationMatrix(Vector(-0.5f));
            actors.push_back((IDrawable*) square);

            square->shaderProgram = colorProgram;
        }

    }

    void LoaderAndScene::OnReshape(int, int) {
//        number aspect = (number) w / (number) h,
//                angle = Maths::ToRadians(30.0f / 2.0f),
//                d = 1.0f / tanf(angle);
//        camera->projection.M[0][0] = d / aspect;
    }

    void LoaderAndScene::PreDraw() {
        if (input.Click(27)) {
            Exit();
        }
        controller.Update();
    }

} /* namespace Divisaction */