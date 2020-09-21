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
#include "../../../3Engine/src/Camera/Perspective.h"
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


class CycleNumber : public IUpdatable {
    public:
        float start{}, step{}, count{}, max{};

        void Update(milliseconds delta) override {
            count += step / delta;
//                if (count > max) {
//                    count = start;
//                }
            if (count > max || count < start) {
                step = -step;
            }
        }
};

class MetallicRoughnessControl : public IUpdatable {
    public:
        float metallic{}, roughness{}, step{};
        Engine* engine{};

        void Update(milliseconds delta) override {
            if (engine->input['q']) {
                metallic -= step / delta;
                if (metallic < 0) {
                    metallic = 0;
                }
            }
            if (engine->input['w']) {
                metallic += step / delta;
                if (metallic > 1) {
                    metallic = 1;
                }
            }
            if (engine->input['e']) {
                roughness -= step / delta;
                if (roughness < 0) {
                    roughness = 0;
                }
            }
            if (engine->input['r']) {
                roughness += step / delta;
                if (roughness > 1) {
                    roughness = 1;
                }
            }
            if (engine->input[SpecialKeys::F1]) {
                roughness += step / delta;
                if (roughness > 1) {
                    roughness = 1;
                }
            }
            if (engine->input[SpecialKeys::F2] && engine->input[SpecialKeys::SHIFT]) {
                roughness += step / delta;
                if (roughness > 1) {
                    roughness = 1;
                }
            }
            if (engine->input[MouseKeys::RIGHT] && engine->input[SpecialKeys::SHIFT]) {
                roughness += step / delta;
                if (roughness > 1) {
                    roughness = 1;
                }
            }
        }
};


Application::Application()
        : Engine(), sceneGraph(new SceneGraph()), controller(this) {}

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
        auto mesh = MeshLoader::instance()->LoadFileOBJ("assets/Cube-vtn.obj");
        MeshManager::instance()->Add("Cube", mesh);
    }
}

void Application::setupTextures() {
    TextureManager::instance()->Add("FortPoint",
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

    {
        auto skySphere = new SkySphere();
        skySphere->setShaderProgram(
                ShaderProgramManager::instance()->Get("skysphere"));
        skySphere->mesh = MeshManager::instance()->Get("Sphere");
        skySphere->textures.push_back(TextureManager::instance()->Get("FortPoint"));
        auto&& hTransform = skySphere->transform;
        hTransform.scale = Vector(100);
        skySphere->SetParent(root);
    }
    {
        auto object = new Actor();
        auto program = ShaderProgramManager::instance()->Get("BRDF");
        object->setShaderProgram(program);
        object->mesh = MeshManager::instance()->Get("Cube");
        object->textures.push_back(TextureManager::instance()->Get("FortPoint"));
        auto&& hTransform = object->transform;
        hTransform.scale = Vector(1);
        hTransform.translation = {0, 10, 0};
        object->preDraw = [program]() {
            glUniform1f(program->GetUniformLocationId("Roughness"), 0.5f);
            glUniform1f(program->GetUniformLocationId("Metallic"), 0.0f);
            glUniform4f(program->GetUniformLocationId("BaseColor"), .6f, .6f, .5f, 1.0f);
        };
        object->SetParent(root);
    }
    {
        auto object = new Actor();
        auto program = ShaderProgramManager::instance()->Get("BRDF");
        object->setShaderProgram(program);
        object->mesh = MeshManager::instance()->Get("Sphere");
        object->textures.push_back(TextureManager::instance()->Get("FortPoint"));
        auto&& hTransform = object->transform;
        hTransform.translation = {-10, 0, 0};
        hTransform.scale = Vector(1);
        object->SetParent(root);

        auto cycleCount = new CycleNumber();
        cycleCount->step = 0.1;
        cycleCount->start = 0;
        cycleCount->max = 1;
        Simulation::instance()->Add(cycleCount);

        object->preDraw = [program, cycleCount]() {
            glUniform1f(program->GetUniformLocationId("Roughness"),
                        cycleCount->count);
            glUniform1f(program->GetUniformLocationId("Metallic"),
                        cycleCount->count);
        };
    }
    {
        auto object = new Actor();
        auto program = ShaderProgramManager::instance()->Get("BRDF");
        object->setShaderProgram(program);
        object->mesh = MeshManager::instance()->Get("Dragon");
        object->textures.push_back(TextureManager::instance()->Get("FortPoint"));
        auto&& hTransform = object->transform;
        hTransform.translation = {10, 0, 0};
        hTransform.scale = Vector(1);
        hTransform.rotation = Quat::FromAngleAxis(-90, Vector(1, 0, 0));
        object->SetParent(root);

        auto shaderController = new MetallicRoughnessControl();
        shaderController->engine = this;
        shaderController->step = 0.1f;
        Simulation::instance()->Add(shaderController);

        object->preDraw = [program, shaderController]() {
            glUniform1f(program->GetUniformLocationId("Roughness"), shaderController->roughness);
            glUniform1f(program->GetUniformLocationId("Metallic"), shaderController->metallic);
            glUniform4f(program->GetUniformLocationId("BaseColor"), 0.6f, 0.1f, 0.1f, 1);
        };
    }


    {
        auto object = new Actor();
        auto program = ShaderProgramManager::instance()->Get("BRDF");
        object->setShaderProgram(program);
        object->mesh = MeshManager::instance()->Get("Cube");
        object->textures.push_back(TextureManager::instance()->Get("FortPoint"));
        auto&& hTransform = object->transform;
        hTransform.scale = Vector(1);
        hTransform.translation = {0, 0, 0};
//        hTransform.rotation = Quat::FromAngleAxis(-45, Vector(0, 1, 0)) +
//                              Quat::FromAngleAxis(-45, Vector(1, 0, 0));
        hTransform.rotation = Quat::FromAngleAxis(-45, Vector(0, 1, 0));
//        hTransform.rotation = Quat::FromAngleAxis(-45, Vector(1, 0, 0));
        object->preDraw = [program]() {
            glUniform1f(program->GetUniformLocationId("Roughness"), 0.5f);
            glUniform1f(program->GetUniformLocationId("Metallic"), 0.0f);
            glUniform4f(program->GetUniformLocationId("BaseColor"), .8f, .8f, .8f, 1.0f);
        };
        object->SetParent(root);
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
    controller.Update();
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