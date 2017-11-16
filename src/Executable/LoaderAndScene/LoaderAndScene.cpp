/*
 * File Tangram.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include <cmath>
#include "LoaderAndScene.h"

#include "../../Engine/Shapes/MeshLoader.h"
#include "../../Engine/Camera/Perspective.h"
#include "../../Engine/Utilities/Managers.h"
#include "../../Engine/Utilities/Simulation.h"
#include "ColoredActor.h"
#include "MoveController.h"

#define VERTICES 0
#define COLORS 1

using json = nlohmann::json;

using namespace std;

namespace ThreeEngine {


    LoaderAndScene::LoaderAndScene()
            : Engine(), sceneGraph(new SceneGraph()), controller() { }

    LoaderAndScene::~LoaderAndScene() = default;

    void LoaderAndScene::OnInit() {
        setupShaders();
        setupMeshes();
        scene();
    }

    void LoaderAndScene::setupShaders() {
        auto defaultProgram = std::make_shared<ShaderProgram>(
                "shaders/Default/program.json");
        defaultProgram->Init();
        ShaderProgramManager::instance()->Add("default", defaultProgram);
        auto colorProgram = std::make_shared<ShaderProgram>(
                "shaders/Color3D/program.json");
        colorProgram->Init();
        ShaderProgramManager::instance()->Add("color3d", colorProgram);
    }

    void LoaderAndScene::setupMeshes() {
        MeshManager::instance()->Add("Cube",
                                     MeshLoader::instance()->LoadFileOBJ(
                                             "assets/Cube-vtn.obj"));
        MeshManager::instance()->Add("Pyramid",
                                     MeshLoader::instance()->LoadFileOBJ(
                                             "assets/Pyramid-vtn.obj"));
        MeshManager::instance()->Add("Parallelogram",
                                     MeshLoader::instance()->LoadFileOBJ(
                                             "assets/Parallelogram-vtn.obj"));
    }

    void LoaderAndScene::scene() {
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
                    new Perspective(30, aspect, 1, 100),
                    new Matrix(Matrix::TranslationMatrix(Vector(0, 0, -30)))
//                    new LookAt({5, 0.5f, 0}, {0, 0.5f, 0}, {0, 1, 0})
            );
            sceneGraph->SetCamera(camera);
            controller.camera = camera;
        }

        auto root = new Actor();
        root->setShaderProgram(
                ShaderProgramManager::instance()->Get("color3d"));
        root->transform.translation = Vector(0, -5, 0);
        sceneGraph->SetRoot(root);

        auto floor = new ColoredActor();
        floor->color = Vector4(.3f, .3f, .3f, 1);
        floor->mesh = MeshManager::instance()->Get("Cube");
        floor->transform.scale = Vector(3, .1f, 3);
        floor->transform.translation = Vector(-3, -.1f, 3);
        floor->SetParent(root);

        const number side = sqrt(16.0f);
        const number hypotenuse = sqrt(side * side * 2);

        {
            { // Big Top Triangle
                auto* pyramid = new ColoredActor();
                pyramid->transform.rotation =
                        Quat::FromAngleAxis(45, Vector(0, 1, 0));
                pyramid->transform.scale = Vector(2);
                pyramid->color = Vector4(.8f, .8f, .5f, 1);
                pyramid->mesh = MeshManager::instance()->Get("Pyramid");
                pyramid->SetParent(root);
            }
            { // Big Left Triangle
                auto* pyramid = new ColoredActor();
                pyramid->transform.rotation =
                        Quat::FromAngleAxis(45 + 90, Vector(0, 1, 0));
                pyramid->transform.scale = Vector(2);
                pyramid->color = Vector4(.8f, .5f, .5f, 1);
                pyramid->mesh = MeshManager::instance()->Get("Pyramid");
                pyramid->SetParent(root);
            }
            { // Small Top Right Triangle
                auto* pyramid = new ColoredActor();
                pyramid->transform.rotation =
                        Quat::FromAngleAxis(-45, Vector(0, 1, 0));
                pyramid->transform.translation = Vector(hypotenuse * .25f, 0,
                                                        -hypotenuse * .25f);
                pyramid->color = Vector4(.8f, .5f, .5f, 1);
                pyramid->mesh = MeshManager::instance()->Get("Pyramid");
                pyramid->SetParent(root);
            }
            { // Square
                auto* cube = new ColoredActor();
                cube->transform.rotation =
                        Quat::FromAngleAxis(-45, Vector(0, 1, 0));
                cube->color = Vector4(.2f, .8f, .5f, 1);
                cube->mesh = MeshManager::instance()->Get("Cube");
                cube->SetParent(root);
            }
            { // Small Center Triangle
                auto* pyramid = new ColoredActor();
                pyramid->transform.rotation =
                        Quat::FromAngleAxis(-45 - 90, Vector(0, 1, 0));
                pyramid->color = Vector4(.6f, .5f, .4f, 1);
                pyramid->mesh = MeshManager::instance()->Get("Pyramid");
                pyramid->SetParent(root);
            }
            { // Parallelogram
                auto* parallelogram = new ColoredActor();
                parallelogram->transform.scale *= Vector(hypotenuse * .25f, hypotenuse * .25f, 1);
                parallelogram->transform.rotation =
                        Quat::FromAngleAxis(-90, Vector(1, 0, 0));
                parallelogram->transform.translation =
                        Vector(-hypotenuse * .5f, 2, hypotenuse * .5f);
                parallelogram->color = Vector4(.2f, .5f, .8f, 1);
                parallelogram->mesh = MeshManager::instance()->Get(
                        "Parallelogram");
                parallelogram->SetParent(root);
            }
            { // Medium Triangle
                auto* pyramid = new ColoredActor();
                pyramid->transform.scale *= Vector(hypotenuse * .25f);
                pyramid->transform.rotation =
                        Quat::FromAngleAxis(90, Vector(0, 1, 0));
                pyramid->transform.translation =
                        Vector(hypotenuse * .5f, 0, hypotenuse * .5f);
                pyramid->color = Vector4(.6f, .5f, .4f, 1);
                pyramid->mesh = MeshManager::instance()->Get("Pyramid");
                pyramid->SetParent(root);
            }
        }

        // Initializes all the actors in it.
        sceneGraph->Init();

        auto moveController = new MoveController();
        moveController->actor = root;
        Simulation::instance()->Add(moveController);
    }

    void LoaderAndScene::OnReshape(int, int) {
//        number aspect = (number) w / (number) h,
//                angle = Maths::ToRadians(30.0f / 2.0f),
//                d = 1.0f / tanf(angle);
//        camera->projection.M[0][0] = d / aspect;
    }

    void LoaderAndScene::PreDraw() {
        controller.Update();
    }

    void LoaderAndScene::Update() {
        if (input.Click(27)) { // ESC
            Exit();
        }
        Simulation::instance()->Update();
    }

    void LoaderAndScene::OnCleanup() {
        ShaderProgramManager::instance()->cleanup();
        MeshManager::instance()->cleanup();
        Simulation::instance()->cleanup();
    }

} /* namespace Divisaction */