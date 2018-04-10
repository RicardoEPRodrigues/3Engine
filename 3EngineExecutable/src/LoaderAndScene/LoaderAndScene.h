/*
 * File Tangram.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_LOADERANDSCENE_H
#define THREEENGINE_LOADERANDSCENE_H

#include "../../Engine/Engine.h"
#include "../../Engine/Controllers/SphereCameraController.h"
#include "../../Engine/Shader/ShaderProgram.h"
#include "../../Engine/IDrawable.h"
#include "../../Engine/SceneManagement/SceneGraph.h"

namespace ThreeEngine {

    class LoaderAndScene : public Engine {
        public:
            LoaderAndScene();

            ~LoaderAndScene() override;

            SceneGraph* sceneGraph;

            SphereCameraController controller;

        protected:

            void OnInit() override;

            void scene();

            void OnReshape(int w, int h) override;

            void PreDraw() override;

            void Update() override;

            void setupShaders();

            void setupMeshes();

            void OnCleanup() override;
    };

} /* namespace Divisaction */

#endif //THREEENGINE_QUATERNION_H
