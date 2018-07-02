/*
 * File Tangram.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include <Shapes/BasicShapes.h>
#include "Tangram3D.h"
#include "../../../3Engine/src/Shapes/MeshLoader.h"
#include "../../../3Engine/src/Shader/TextureLoader.h"
#include "../../../3Engine/src/Camera/Perspective.h"
#include "../../../3Engine/src/Utilities/Managers.h"
#include "../../../3Engine/src/Utilities/Simulation.h"
#include "../../../3Engine/src/Actors/SkySphere.h"

#define VERTICES 0
#define COLORS 1

using json = nlohmann::json;

int main(int argc, char* argv[]) {
    srand(static_cast <unsigned> (time(0)));

    {
        ThreeEngine::Tangram3D engine;
        engine.Init(argc, argv);
        engine.Run();
    }

    exit(EXIT_SUCCESS);
}

namespace ThreeEngine {


    Tangram3D::Tangram3D()
            : Engine(), sceneGraph(new SceneGraph()), controller() {}

    Tangram3D::~Tangram3D() = default;

    void Tangram3D::OnInit() {
        setupShaders();
        setupMeshes();
        setupTextures();
        scene();
    }

    void Tangram3D::setupShaders() {
        auto colorProgram = std::make_shared<ShaderProgram>(
                "shaders/Color3D/program.json");
        colorProgram->Init();
        ShaderProgramManager::instance()->Add("color3d", colorProgram);
        ShaderProgramManager::instance()->Add("default", colorProgram);
        auto skysphere = std::make_shared<ShaderProgram>(
                "shaders/SkySphere/program.json");
        skysphere->Init();
        ShaderProgramManager::instance()->Add("skysphere", skysphere);
    }

    void Tangram3D::setupMeshes() {
        MeshManager::instance()->Add("Cube",
                                     MeshLoader::instance()->LoadFileOBJ("assets/Cube-vtn.obj"));
    }

    void Tangram3D::setupTextures() {
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

    void Tangram3D::scene() {
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

        auto colorProgram = ShaderProgramManager::instance()->Get("color3d");
        auto root = new Actor();
        root->setShaderProgram(colorProgram);
        sceneGraph->SetRoot(root);

        float triangleSize = 0.7071f;


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

        Vector4 defaultColor = {.1f, .1f, .5f, 1.0f};

        { // Big triangle to the Left
            auto* shape = new Actor();
            shape->mesh = BasicShapes::TriangularParallelepiped(triangleSize * 2);
            shape->transform.rotation = Quat::FromAngleAxis(135, Vector::UpVector);
            shape->SetParent(root);
            Vector4 color = defaultColor;
            color[0] = .5f;
            shape->preDraw = [shape, color]() {
                glUniform4f(shape->GetShaderProgram()->GetUniformLocationId("ModelColor"),
                            color[0],
                            color[1],
                            color[2],
                            color[3]);
            };
        }
        { // Big triangle to the Top

            auto* shape = new Actor();
            shape->mesh = BasicShapes::TriangularParallelepiped(triangleSize * 2);
            shape->transform.translation = {0, 0, .5f};
            shape->transform.rotation = Quat::FromAngleAxis(45, Vector::UpVector);
            shape->SetParent(root);
            Vector4 color = defaultColor;
            color[1] = .5f;
            shape->preDraw = [shape, color]() {
                glUniform4f(shape->GetShaderProgram()->GetUniformLocationId("ModelColor"),
                            color[0],
                            color[1],
                            color[2],
                            color[3]);
            };
        }
        { // Small triangle at the center
            auto* shape = new Actor();
            shape->mesh = BasicShapes::TriangularParallelepiped(triangleSize);
            shape->transform.translation = {0, 0, -.5f};
            shape->transform.rotation = Quat::FromAngleAxis(-135, Vector::UpVector);
            shape->SetParent(root);
            const Vector4& color = defaultColor;
            shape->preDraw = [shape, color]() {
                glUniform4f(shape->GetShaderProgram()->GetUniformLocationId("ModelColor"),
                            color[0],
                            color[1],
                            color[2],
                            color[3]);
            };
        }
        { // Small triangle at the top right
            auto* shape = new Actor();
            shape->mesh = BasicShapes::TriangularParallelepiped(triangleSize);
            shape->transform.translation = {0.5f, 0.5f, .2f};
            shape->transform.rotation = Quat::FromAngleAxis(-45, Vector::UpVector);
            shape->SetParent(root);
            Vector4 color = defaultColor;
            color[0] = .5f;
            color[1] = .5f;
            shape->preDraw = [shape, color]() {
                glUniform4f(shape->GetShaderProgram()->GetUniformLocationId("ModelColor"),
                            color[0],
                            color[1],
                            color[2],
                            color[3]);
            };
        }
        { // Medium triangle to the bottom right
            auto* shape = new Actor();
            shape->mesh = BasicShapes::TriangularParallelepiped();
            shape->transform.translation = {1, -1, -.2f};
            shape->transform.rotation = Quat::FromAngleAxis(90, Vector::UpVector);
            shape->SetParent(root);
            Vector4 color = defaultColor;
            color[0] = .2f;
            color[1] = .7f;
            shape->preDraw = [shape, color]() {
                glUniform4f(shape->GetShaderProgram()->GetUniformLocationId("ModelColor"),
                            color[0],
                            color[1],
                            color[2],
                            color[3]);
            };
        }
        { // Square
            auto* shape = new Actor();
            bool fromObj = true;
            if (fromObj) {
                shape->mesh = MeshManager::instance()->Get("Cube");
                shape->transform.scale = Vector(triangleSize / 2.0f);
                shape->transform.translation = {0, 0, 1};

            } else {
                shape->mesh = BasicShapes::Cube(triangleSize);
                shape->transform.translation = {.5f, 0, 1};
            }
            shape->transform.rotation = Quat::FromAngleAxis(-45, Vector::UpVector);
            shape->SetParent(root);
            Vector4 color = defaultColor;
            color[0] = .2f;
            color[2] = .7f;
            shape->preDraw = [shape, color]() {
                glUniform4f(shape->GetShaderProgram()->GetUniformLocationId("ModelColor"),
                            color[0],
                            color[1],
                            color[2],
                            color[3]);
            };

        }
        {
            auto* shape = new Actor();
            shape->mesh = BasicShapes::SquaredParallelepiped();
            shape->transform.translation = {-1, -1, -1};
            shape->SetParent(root);
            Vector4 color = defaultColor;
            color[1] = .2f;
            color[2] = .7f;
            shape->preDraw = [shape, color]() {
                glUniform4f(shape->GetShaderProgram()->GetUniformLocationId("ModelColor"),
                            color[0],
                            color[1],
                            color[2],
                            color[3]);
            };
        }


//        sceneGraph->Init();
        for (auto&& actor : actors) {
            actor->Init();
        }
    }

    void Tangram3D::OnReshape(int, int) {
//        number aspect = (number) w / (number) h,
//                angle = Maths::ToRadians(30.0f / 2.0f),
//                d = 1.0f / tanf(angle);
//        camera->projection.M[0][0] = d / aspect;
    }

    void Tangram3D::PreDraw() {
        controller.Update();
    }

    void Tangram3D::Update() {
        if (input.Click(27)) { // ESC
            Exit();
        }
        Simulation::instance()->Update();
    }

    void Tangram3D::OnCleanup() {
        ShaderProgramManager::instance()->cleanup();
        MeshManager::instance()->cleanup();
        Simulation::instance()->cleanup();
    }

} /* namespace Divisaction */