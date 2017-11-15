/*
 * File Tangram.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "LoaderAndScene.h"
#include "../../Engine/Actor.h"
#include "../../Engine/Shapes/Cube.h"
#include "../../Engine/Shapes/MeshLoader.h"
#include "../../Engine/Camera/Perspective.h"
#include "../../Engine/Utilities/Managers.h"

#define VERTICES 0
#define COLORS 1

using json = nlohmann::json;

namespace ThreeEngine {


    LoaderAndScene::LoaderAndScene()
            : Engine(), sceneGraph(new SceneGraph()), controller() { }

    LoaderAndScene::~LoaderAndScene() = default;

    void LoaderAndScene::OnInit() {
        scene();
    }

    void LoaderAndScene::scene() {
        { // Shaders
            auto defaultProgram = std::make_shared<ShaderProgram>(
                    "shaders/Default/program.json");
            defaultProgram->Init();
            ShaderProgramManager::instance()->Add("default", defaultProgram);
            auto colorProgram = std::make_shared<ShaderProgram>(
                    "shaders/Color3D/program.json");
            colorProgram->Init();
            ShaderProgramManager::instance()->Add("color3d", colorProgram);
        }

        MeshManager::instance()->Add("Cube", 
            MeshLoader::instance()->LoadFileOBJ("assets/Cube-vtn.obj"));

        actors.push_back(reinterpret_cast<IDrawable*&&>(sceneGraph));

        { // Camera handling
            number width = config["window"]["x"];
            number height = config["window"]["y"];
            number aspect = width / height;
            Camera* camera = new Camera(
                    static_cast<GLuint>(
                        ShaderProgramManager::instance()->Get("default")
                        ->GetUniformBlockBidingId("SharedMatrices")),
                    new Perspective(30, aspect, 1, 100),
                    new Matrix(Matrix::TranslationMatrix(Vector(0, 0, -15)))
//                    new LookAt({5, 0.5f, 0}, {0, 0.5f, 0}, {0, 1, 0})
            );
            sceneGraph->SetCamera(camera);
            controller.camera = camera;
        }

        //{
        //    auto* cube = new Actor();
        //    cube->mesh = MeshManager::instance()->Get("Cube");

        //    sceneGraph->SetRoot(cube);

        //    auto* cube2 = new Actor();
        //    cube2->mesh = cube->mesh;
        //    cube2->transform.translation += Vector(0, 2, 0);
        //    cube2->SetParent(cube);
        //}

        { // Square
            auto root = new Actor();
            root->shaderProgram =
                ShaderProgramManager::instance()->Get("default");
            sceneGraph->SetRoot(root);

            {
                auto square = new Cube();
                square->color[0] = 1;
                square->color[1] = 0;
                square->color[2] = 1;
                square->color[3] = 1;
                square->shaderProgram = ShaderProgramManager::instance()->Get("color3d");
                square->transform.scale = Vector(.5f);
                square->transform.rotation =
                    Quat::FromAngleAxis(45, Vector(0, 0, -1));
                square->SetParent(root);

                auto* cube2 = new Actor();
                cube2->mesh = MeshManager::instance()->Get("Cube");
                cube2->transform.translation += Vector(0, 2, 0);
                cube2->SetParent(square);
            }

            auto* cube3 = new Actor();
            cube3->mesh = MeshManager::instance()->Get("Cube");
            cube3->transform.translation += Vector(0, 2, 0);
            cube3->SetParent(root);
        }

        // Initializes all the actors in it.
        sceneGraph->Init();
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