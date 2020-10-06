/*
 * File Tangram.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_LIGHTSCENE_H
#define THREEENGINE_LIGHTSCENE_H

#include "../../../3Engine/src/Engine.h"
#include "../../../3Engine/src/Controllers/SphereCameraController.h"
#include "../../../3Engine/src/Shader/ShaderProgram.h"
#include "../../../3Engine/src/IDrawable.h"
#include "../../../3Engine/src/SceneManagement/SceneGraph.h"

class Application : public ThreeEngine::Engine {
    public:
        Application();

        ~Application() override;

        ThreeEngine::SceneGraph* sceneGraph;

        ThreeEngine::SphereCameraController cameraController;

    protected:

        void OnInit() override;

        void scene();

        void OnReshape(int w, int h) override;

        void PreDraw() override;

        void Update() override;

        void setupShaders();

        void setupMeshes();

        void setupTextures();

        void OnCleanup() override;
};

class LShape : public ThreeEngine::Actor {
    public:
        LShape();
};

class LInverseShape : public ThreeEngine::Actor {
    public:
        LInverseShape();
};

class SquareShape : public ThreeEngine::Actor {
    public:
        SquareShape();
};

class LineShape : public ThreeEngine::Actor {
    public:
        LineShape();
};

#endif //THREEENGINE_LIGHTSCENE_H
