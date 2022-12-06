/*
 * File Tangram.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include <cmath>
#include "MyEngine.h"

#include "../../../3Engine/src/Shapes/MeshLoader.h"
#include "../../../3Engine/src/Shader/TextureLoader.h"
#include "../../../3Engine/src/Camera/Camera.h"
#include "../../../3Engine/src/Utilities/Managers.h"
#include "../../../3Engine/src/Utilities/Simulation.h"
#include "../../../3Engine/src/Actors/SkySphere.h"

using json = nlohmann::json;

using namespace std;
using namespace ThreeEngine;
using namespace Executable;

int main(int argc, char* argv[]) {
    srand(static_cast <unsigned> (time(0)));

    {
        MyEngine engine;
        engine.Init(argc, argv);
        engine.Run();
    }

    exit(EXIT_SUCCESS);
}

namespace Executable {

    MyEngine::MyEngine()
            : Engine(), sceneGraph(new SceneGraph()), controller(this) { }

    MyEngine::~MyEngine() = default;

    void MyEngine::OnInit() {
        setupShaders();
        setupMeshes();
        setupTextures();
        scene();
    }

    void MyEngine::setupShaders() {
        auto skysphere = std::make_shared<ShaderProgram>(
                "shaders/SkySphere/program.json");
        skysphere->Init();
        ShaderProgramManager::instance()->Add("skysphere", skysphere);
        auto defaultProgram = std::make_shared<ShaderProgram>(
                "shaders/Default/program.json");
        defaultProgram->Init();
        ShaderProgramManager::instance()->Add("Default", defaultProgram);
        auto timeProgram = std::make_shared<ShaderProgram>(
                "shaders/TimeMovingTexture/program.json");
        timeProgram->Init();
        ShaderProgramManager::instance()->Add("Time", timeProgram);
    }

    void MyEngine::setupMeshes() {
        MeshManager::instance()->Add("Sphere",
                                     MeshLoader::instance()->LoadFileOBJ(
                                             "assets/Sphere.obj"));
    }

    void MyEngine::setupTextures() {
        TextureManager::instance()->Add("Stone",
                                        TextureLoader::instance()->LoadTexture(
                                                "assets/Stone.jpg"));
        TextureManager::instance()->Add("GGB3",
                                        TextureLoader::instance()->LoadCubemap(
                                                "assets/GoldenGateBridge3/negz.jpg",
                                                "assets/GoldenGateBridge3/posz.jpg",
                                                "assets/GoldenGateBridge3/posy.jpg",
                                                "assets/GoldenGateBridge3/negy.jpg",
                                                "assets/GoldenGateBridge3/negx.jpg",
                                                "assets/GoldenGateBridge3/posx.jpg"
                                        ));
    }

    void MyEngine::scene() {
        actors.push_back(reinterpret_cast<IDrawable*&&>(sceneGraph));

        { // Camera handling
            number width = config["window"]["x"];
            number height = config["window"]["y"];
            Camera* camera = new Camera(
                    static_cast<GLuint>(
                            ShaderProgramManager::instance()->Get(
                                    "Time")->GetUniformBlockBidingId(
                                    "SharedMatrices")),
                    new PerspectiveCameraMatrix(30, width, height, 1, 1000),
                    new CameraMatrix(Matrix::TranslationMatrix(Vector(0, 0, -100)))
//                    new LookAt({5, 0.5f, 0}, {0, 0.5f, 0}, {0, 1, 0})
            );
            sceneGraph->SetCamera(camera);
            controller.camera = camera;
        }

        auto root = new Actor();
        root->setShaderProgram(
                ShaderProgramManager::instance()->Get("Default"));
        sceneGraph->SetRoot(root);

        {
            auto object = new Actor();
            auto program = ShaderProgramManager::instance()->Get("Time");
            object->setShaderProgram(program);
            object->mesh = MeshManager::instance()->Get("Sphere");
            object->textures.push_back(
                    TextureManager::instance()->Get("Stone"));
            auto&& hTransform = object->transform;
            hTransform.scale = Vector(10);
            object->SetParent(root);

            object->preDraw = [program]() {
                glUniform1f(program->GetUniformLocationId("Time"),
                            Time::Now()/1000.0f);
            };
        }
        {
            auto skySphere = new SkySphere();
            skySphere->setShaderProgram(
                    ShaderProgramManager::instance()->Get("skysphere"));
            skySphere->mesh = MeshManager::instance()->Get("Sphere");
            skySphere->textures.push_back(
                    TextureManager::instance()->Get("GGB3"));
            auto&& hTransform = skySphere->transform;
            hTransform.scale = Vector(100);
            skySphere->SetParent(root);
        }

        // Initializes all the actors in it.
        sceneGraph->Init();
    }

    void MyEngine::OnReshape(int, int) {
//        number aspect = (number) w / (number) h,
//                angle = Maths::ToRadians(30.0f / 2.0f),
//                d = 1.0f / tanf(angle);
//        camera->projection.M[0][0] = d / aspect;
    }

    void MyEngine::PreDraw() {
        controller.Update();
    }

    void MyEngine::Update() {
        if (input.Click(27)) { // ESC
            Exit();
        }
        Simulation::instance()->Update();
    }

    void MyEngine::OnCleanup() {
        ShaderProgramManager::instance()->cleanup();
        MeshManager::instance()->cleanup();
        Simulation::instance()->cleanup();
    }

} /* namespace Divisaction */