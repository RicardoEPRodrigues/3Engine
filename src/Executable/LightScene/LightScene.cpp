/*
 * File Tangram.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include <cmath>
#include "LightScene.h"

#include "../../Engine/Shapes/MeshLoader.h"
#include "../../Engine/Camera/Perspective.h"
#include "../../Engine/Utilities/Managers.h"
#include "../../Engine/Utilities/Simulation.h"

#define VERTICES 0
#define COLORS 1

using json = nlohmann::json;

using namespace std;

namespace ThreeEngine {


    LightScene::LightScene()
            : Engine(), sceneGraph(new SceneGraph()), controller() { }

    LightScene::~LightScene() = default;

    void LightScene::OnInit() {
        setupShaders();
        setupMeshes();
        scene();
    }

    void LightScene::setupShaders() {
        auto defaultProgram = std::make_shared<ShaderProgram>(
                "shaders/Default/program.json");
        defaultProgram->Init();
        ShaderProgramManager::instance()->Add("default", defaultProgram);
    }

    void LightScene::setupMeshes() {
        MeshManager::instance()->Add("Horse",
                                     MeshLoader::instance()->LoadFileOBJ(
                                             "assets/Horse-vtn.obj"));
    }

    void LightScene::scene() {
        actors.push_back(reinterpret_cast<IDrawable*&&>(sceneGraph));

        { // Camera handling
            number width = config["window"]["x"];
            number height = config["window"]["y"];
            number aspect = width / height;
            Camera* camera = new Camera(
                    static_cast<GLuint>(
                            ShaderProgramManager::instance()->Get(
                                    "default")->GetUniformBlockBidingId(
                                    "SharedMatrices")),
                    new Perspective(30, aspect, 1, 1000),
                    new Matrix(Matrix::TranslationMatrix(Vector(0, 0, -100)))
//                    new LookAt({5, 0.5f, 0}, {0, 0.5f, 0}, {0, 1, 0})
            );
            sceneGraph->SetCamera(camera);
            controller.camera = camera;
        }

        auto root = new Actor();
        root->setShaderProgram(
                ShaderProgramManager::instance()->Get("default"));
        sceneGraph->SetRoot(root);

        auto horse = new Actor();
        horse->mesh = MeshManager::instance()->Get("Horse");
        auto&& hTransform = horse->transform;
        hTransform.scale = Vector(0.1f);
        hTransform.translation.Y = -10;
        horse->SetParent(root);

        // Initializes all the actors in it.
        sceneGraph->Init();
    }

    void LightScene::OnReshape(int, int) {
//        number aspect = (number) w / (number) h,
//                angle = Maths::ToRadians(30.0f / 2.0f),
//                d = 1.0f / tanf(angle);
//        camera->projection.M[0][0] = d / aspect;
    }

    void LightScene::PreDraw() {
        controller.Update();
    }

    void LightScene::Update() {
        if (input.Click(27)) { // ESC
            Exit();
        }
        Simulation::instance()->Update();
    }

    void LightScene::OnCleanup() {
        ShaderProgramManager::instance()->cleanup();
        MeshManager::instance()->cleanup();
        Simulation::instance()->cleanup();
    }

} /* namespace Divisaction */