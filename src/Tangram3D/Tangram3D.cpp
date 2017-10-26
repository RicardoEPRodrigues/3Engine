/*
 * File Tangram.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "Tangram3D.h"
#include "Cube.h"
#include "../Camera/Perspective.h"
#include "../Camera/LookAt.h"

#define VERTICES 0
#define COLORS 1

using json = nlohmann::json;

namespace ThreeEngine {


    Tangram3D::Tangram3D() : Engine(), shapeToShow(CUBE), controller() { }

    Tangram3D::~Tangram3D() = default;

    void Tangram3D::OnInit() {
        switch (shapeToShow) {
            case CUBE:
                CubeScene();
                break;
        }
    }

    void Tangram3D::CubeScene() {
        auto colorProgram = std::make_shared<ShaderProgram>("shaders/Color3D/program.json");
        colorProgram->Init();

        Debug::Log(*colorProgram);

        { // Camera handling
            if (camera) {
                delete camera;
            }

            number width = config["window"]["x"];
            number height = config["window"]["y"];
            number aspect = width / height;
            camera = new Camera(
                    static_cast<GLuint>(colorProgram->GetUniformBlockBidingId("SharedMatrices")),
                    new Perspective(30, aspect, 1, 100),
                    new LookAt({5, 5, 5}, {0, 0, 0}, {0, 1, 0}));
        }

        {
            auto* cube = new Cube();
            actors.push_back((IActor*) cube);

            cube->shaderProgram = colorProgram;
        }

    }

    void Tangram3D::OnReshape(int, int) {
//        number aspect = (number) w / (number) h,
//                angle = Maths::ToRadians(30.0f / 2.0f),
//                d = 1.0f / tanf(angle);
//        camera->projection.M[0][0] = d / aspect;
    }

    void Tangram3D::PreDraw() {
        if (input.Click(27)) {
            Exit();
        }
        controller.Update();
    }

} /* namespace Divisaction */