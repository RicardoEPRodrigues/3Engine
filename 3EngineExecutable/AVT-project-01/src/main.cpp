/*
 * File Tangram.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include <cmath>
#include <ctime>
#include "main.h"

#include "../../../3Engine/src/Shapes/MeshLoader.h"
#include "../../../3Engine/src/Shader/TextureLoader.h"
#include "../../../3Engine/src/Camera/Ortho.h"
#include "../../../3Engine/src/Utilities/Managers.h"
#include "../../../3Engine/src/Utilities/Simulation.h"
#include "../../../3Engine/src/Actors/SkySphere.h"
#include "../../../3Engine/src/Shapes/BasicShapes.h"

using json = nlohmann::json;
using namespace std;
using namespace ThreeEngine;

int main(int argc, char* argv[]) {
    auto seed = static_cast <unsigned> (time(nullptr));
    srand(seed);

    {
        Application engine;
        engine.Init(argc, argv);
        engine.Run();
    }

    exit(EXIT_SUCCESS);
}

class RotationControl : public IUpdatable {
    public:
        Vector EulerAngles{};
        Engine* engine;
        Actor* actor;
        float step{};

        RotationControl(Engine* engine, Actor* actor) {
            this->engine = engine;
            this->actor = actor;
            this->step = 5.0f;
        }

        void Update(milliseconds delta) override {
            auto&& hTransform = actor->transform;
            if (engine->input['r']) {
                EulerAngles.X += step * (delta / 1000.0f);
                Debug::Log("Euler Angles: %s", static_cast<string>(EulerAngles).c_str());
            }
            if (engine->input['f']) {
                EulerAngles.X -= step * (delta / 1000.0f);
                Debug::Log("Euler Angles: %s", static_cast<string>(EulerAngles).c_str());
            }
            if (engine->input['t']) {
                EulerAngles.Y += step * (delta / 1000.0f);
                Debug::Log("Euler Angles: %s", static_cast<string>(EulerAngles).c_str());
            }
            if (engine->input['g']) {
                EulerAngles.Y -= step * (delta / 1000.0f);
                Debug::Log("Euler Angles: %s", static_cast<string>(EulerAngles).c_str());
            }
            if (engine->input['y']) {
                EulerAngles.Z += step * (delta / 1000.0f);
                Debug::Log("Euler Angles: %s", static_cast<string>(EulerAngles).c_str());
            }
            if (engine->input['h']) {
                EulerAngles.Z -= step * (delta / 1000.0f);
                Debug::Log("Euler Angles: %s", static_cast<string>(EulerAngles).c_str());
            }
            hTransform.rotation = Quat::FromEulerAngles(EulerAngles);
        }
};


Application::Application()
        : Engine(), sceneGraph(new SceneGraph()), cameraController(this) {}

Application::~Application() = default;

void Application::OnInit() {
    setupShaders();
    setupMeshes();
    setupTextures();
    scene();
}

void Application::setupShaders() {
    {
        auto program = std::make_shared<ShaderProgram>("shaders/Default/program.json");
        program->Init();
        ShaderProgramManager::instance()->Add("default", program);
    }
    {
        auto program = std::make_shared<ShaderProgram>("shaders/BRDF/program.json");
        program->Init();
        ShaderProgramManager::instance()->Add("BRDF", program);
    }
    {
        auto program = std::make_shared<ShaderProgram>("shaders/SkySphere/program.json");
        program->Init();
        ShaderProgramManager::instance()->Add("skysphere", program);
    }
}

void Application::setupMeshes() {
    MeshManager::instance()->Add("Horse",
                                 MeshLoader::instance()->LoadFileOBJ("assets/Horse-vtn.obj"));
//    MeshManager::instance()->Add("Cube",
//                                 MeshLoader::instance()->LoadFileOBJ(
//                                         "assets/Cube-vtn.obj"));
    MeshManager::instance()->Add("Sphere",
                                 MeshLoader::instance()->LoadFileOBJ("assets/Sphere.obj"));
    MeshManager::instance()->Add("Dragon",
                                 MeshLoader::instance()->LoadFileOBJ("assets/dragon_smooth.obj"));
    {
        auto mesh = MeshLoader::instance()->LoadFileOBJ("assets/cube.obj");
        MeshManager::instance()->Add("Cube", mesh);
    }
}

void Application::setupTextures() {
    TextureManager::instance()->Add("skysphere",
                                    TextureLoader::instance()->LoadCubemap(
                                            "assets/FortPoint/negz.jpg",
                                            "assets/FortPoint/posz.jpg",
                                            "assets/FortPoint/posy.jpg",
                                            "assets/FortPoint/negy.jpg",
                                            "assets/FortPoint/negx.jpg",
                                            "assets/FortPoint/posx.jpg"
                                    ));
}

void Application::scene() {
    actors.push_back(reinterpret_cast<IDrawable*&&>(sceneGraph));

    { // Camera handling
//        number width = config["window"]["x"];
//        number height = config["window"]["y"];
//        number aspect = width / height;
        Camera* camera = new Camera(
                static_cast<GLuint>(
                        ShaderProgramManager::instance()->Get(
                                "default")->GetUniformBlockBidingId(
                                "SharedMatrices")),
//                new Perspective(30, aspect, 1, 1000),
                new Ortho(-30, 30, -30, 30, 1, 1000),
                new Matrix(Matrix::TranslationMatrix(Vector(0, 0, -100)))
//                    new LookAt({5, 0.5f, 0}, {0, 0.5f, 0}, {0, 1, 0})
        );
        sceneGraph->SetCamera(camera);
        cameraController.camera = camera;
    }

    auto root = new Actor();
    root->setShaderProgram(
            ShaderProgramManager::instance()->Get("default"));
    sceneGraph->SetRoot(root);

    {
        auto skySphere = new SkySphere();
        skySphere->setShaderProgram(
                ShaderProgramManager::instance()->Get("skysphere"));
        skySphere->mesh = MeshManager::instance()->Get("Sphere");
        skySphere->textures.push_back(TextureManager::instance()->Get("skysphere"));
        auto&& hTransform = skySphere->transform;
        hTransform.scale = Vector(100);
        skySphere->SetParent(root);
    }

    {
        auto cubeRow = new Actor();

        auto&& hTransform = cubeRow->transform;
        hTransform.scale = Vector(3);
        hTransform.translation = {0, -10, 0};
        Vector EulerAngles = { 45, -35, 29 };
        hTransform.rotation = Quat::FromEulerAngles(EulerAngles);

        auto controller = new RotationControl(this, cubeRow);
        controller->EulerAngles = EulerAngles;
        Simulation::instance()->Add(controller);

        {
            // RIGHT
            // Rendering Order matters!

            // This object needs to be drawn before the next object.
            {
                auto object = new Actor();
                auto program = ShaderProgramManager::instance()->Get("BRDF");
                object->setShaderProgram(program);
                object->mesh = MeshManager::instance()->Get("Cube");
                object->textures.push_back(TextureManager::instance()->Get("skysphere"));
                auto&& hTransform = object->transform;
                hTransform.translation = {0, 2.5f, 0};

                object->preDraw = [program]() {
                    glUniform1f(program->GetUniformLocationId("Roughness"), 0.5f);
                    glUniform1f(program->GetUniformLocationId("Metallic"), 0.0f);
                    glUniform4f(program->GetUniformLocationId("BaseColor"), .8f, .8f, .8f, 1.0f);
                };
                object->SetParent(cubeRow);
            }

            // This object is drawn without Depth masking (Z-buffer disabled).
            {
                auto object = new Actor();
                auto program = ShaderProgramManager::instance()->Get("BRDF");
                object->setShaderProgram(program);
                object->mesh = MeshManager::instance()->Get("Cube");
                object->textures.push_back(TextureManager::instance()->Get("skysphere"));
                auto&& hTransform = object->transform;
                hTransform.translation = {0, 5.f, 0};

                object->preDraw = [program]() {
                    glUniform1f(program->GetUniformLocationId("Roughness"), 0.5f);
                    glUniform1f(program->GetUniformLocationId("Metallic"), 0.0f);
                    glUniform4f(program->GetUniformLocationId("BaseColor"), .8f, .8f, .8f, 1.0f);

                    glDepthMask(GL_FALSE);
                };
                object->postDraw = []() {
                    glDepthMask(GL_TRUE);
                };
                object->SetParent(cubeRow);
            }

            // START AND LEFT
            auto object = new Actor();
            auto program = ShaderProgramManager::instance()->Get("BRDF");
            object->setShaderProgram(program);
            object->mesh = MeshManager::instance()->Get("Cube");
            object->textures.push_back(TextureManager::instance()->Get("skysphere"));
            auto&& hTransform = object->transform;
            hTransform.translation = {0, 0, 0};

            object->preDraw = [program]() {
                glUniform1f(program->GetUniformLocationId("Roughness"), 0.5f);
                glUniform1f(program->GetUniformLocationId("Metallic"), 0.0f);
                glUniform4f(program->GetUniformLocationId("BaseColor"), .8f, .8f, .8f, 1.0f);
            };
            object->SetParent(cubeRow);
        }

        {
            auto object = new Actor();
            auto program = ShaderProgramManager::instance()->Get("BRDF");
            object->setShaderProgram(program);
            object->mesh = MeshManager::instance()->Get("Cube");
            object->textures.push_back(TextureManager::instance()->Get("skysphere"));
            auto&& hTransform = object->transform;
            hTransform.translation = {-2.5f, 0, 0};

            object->preDraw = [program]() {
                glUniform1f(program->GetUniformLocationId("Roughness"), 0.5f);
                glUniform1f(program->GetUniformLocationId("Metallic"), 0.0f);
                glUniform4f(program->GetUniformLocationId("BaseColor"), .8f, .8f, .8f, 1.0f);
            };
            object->SetParent(cubeRow);
        }

        {
            auto object = new Actor();
            auto program = ShaderProgramManager::instance()->Get("BRDF");
            object->setShaderProgram(program);
            object->mesh = MeshManager::instance()->Get("Cube");
            object->textures.push_back(TextureManager::instance()->Get("skysphere"));
            auto&& hTransform = object->transform;
            hTransform.translation = {-5.0f, 0, 0};

            object->preDraw = [program]() {
                glUniform1f(program->GetUniformLocationId("Roughness"), 0.5f);
                glUniform1f(program->GetUniformLocationId("Metallic"), 0.0f);
                glUniform4f(program->GetUniformLocationId("BaseColor"), .8f, .8f, .8f, 1.0f);
            };
            object->SetParent(cubeRow);
        }

        {
            auto object = new Actor();
            auto program = ShaderProgramManager::instance()->Get("BRDF");
            object->setShaderProgram(program);
            object->mesh = MeshManager::instance()->Get("Cube");
            object->textures.push_back(TextureManager::instance()->Get("skysphere"));
            auto&& hTransform = object->transform;
            hTransform.translation = {-7.5f, 0, 0};

            object->preDraw = [program]() {
                glUniform1f(program->GetUniformLocationId("Roughness"), 0.5f);
                glUniform1f(program->GetUniformLocationId("Metallic"), 0.0f);
                glUniform4f(program->GetUniformLocationId("BaseColor"), .8f, .8f, .8f, 1.0f);
            };
            object->SetParent(cubeRow);
        }

        // TOP LEFT

        {
            auto object = new Actor();
            auto program = ShaderProgramManager::instance()->Get("BRDF");
            object->setShaderProgram(program);
            object->mesh = MeshManager::instance()->Get("Cube");
            object->textures.push_back(TextureManager::instance()->Get("skysphere"));
            auto&& hTransform = object->transform;
            hTransform.translation = {-7.5f, 0, -2.5};

            object->preDraw = [program]() {
                glUniform1f(program->GetUniformLocationId("Roughness"), 0.5f);
                glUniform1f(program->GetUniformLocationId("Metallic"), 0.0f);
                glUniform4f(program->GetUniformLocationId("BaseColor"), .8f, .8f, .8f, 1.0f);
            };
            object->SetParent(cubeRow);
        }

        {
            auto object = new Actor();
            auto program = ShaderProgramManager::instance()->Get("BRDF");
            object->setShaderProgram(program);
            object->mesh = MeshManager::instance()->Get("Cube");
            object->textures.push_back(TextureManager::instance()->Get("skysphere"));
            auto&& hTransform = object->transform;
            hTransform.translation = {-7.5f, 0, -5.0f};

            object->preDraw = [program]() {
                glUniform1f(program->GetUniformLocationId("Roughness"), 0.5f);
                glUniform1f(program->GetUniformLocationId("Metallic"), 0.0f);
                glUniform4f(program->GetUniformLocationId("BaseColor"), .8f, .8f, .8f, 1.0f);
            };
            object->SetParent(cubeRow);
        }

        {
            auto object = new Actor();
            auto program = ShaderProgramManager::instance()->Get("BRDF");
            object->setShaderProgram(program);
            object->mesh = MeshManager::instance()->Get("Cube");
            object->textures.push_back(TextureManager::instance()->Get("skysphere"));
            auto&& hTransform = object->transform;
            hTransform.translation = {-7.5f, 0, -7.5f};

            object->preDraw = [program]() {
                glUniform1f(program->GetUniformLocationId("Roughness"), 0.5f);
                glUniform1f(program->GetUniformLocationId("Metallic"), 0.0f);
                glUniform4f(program->GetUniformLocationId("BaseColor"), .8f, .8f, .8f, 1.0f);
            };
            object->SetParent(cubeRow);
        }

        cubeRow->SetParent(root);
    }



    // Initializes all the actors in it.
    sceneGraph->Init();
}

void Application::OnReshape(int, int) {
//        number aspect = (number) w / (number) h,
//                angle = Maths::ToRadians(30.0f / 2.0f),
//                d = 1.0f / tanf(angle);
//        camera->projection.M[0][0] = d / aspect;
}

void Application::PreDraw() {
    cameraController.Update();
}

void Application::Update() {
    if (input.Click(27)) { // ESC
        Exit();
    }
    Simulation::instance()->Update();
}

void Application::OnCleanup() {
    ShaderProgramManager::instance()->cleanup();
    MeshManager::instance()->cleanup();
    Simulation::instance()->cleanup();
}