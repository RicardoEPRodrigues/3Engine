/*
 * File Tangram.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "Tangram3D.h"
#include "../Debug.h"
#include "Cube.h"
#include "../Camera.h"

#define VERTICES 0
#define COLORS 1

using json = nlohmann::json;

namespace ThreeEngine {


    Tangram3D::Tangram3D() : Engine(), shapeToShow(CUBE) {}

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

        {
            auto* camera = new Camera();
            camera->uniformBlockBidingID = static_cast<GLuint>(colorProgram->GetUniformBlockBidingId(
                    "SharedMatrices"));
            actors.push_back((IActor*) camera);
        }

        {
            auto* cube = new Cube();
            actors.push_back((IActor*) cube);

            cube->shaderProgram = colorProgram;
        }
    }

} /* namespace Divisaction */