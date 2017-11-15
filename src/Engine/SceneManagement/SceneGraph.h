/*
 * File SceneGraph.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_SCENEGRAPH_H
#define THREEENGINE_SCENEGRAPH_H

#include "../IDrawable.h"
#include "../Actor.h"
#include "../Camera/Camera.h"
#include "../Utilities/singleton.h"

namespace ThreeEngine {

    class SceneGraph : public IDrawable{
            Actor* root = nullptr;

            Camera* camera;

        public:

            SceneGraph();

            ~SceneGraph() override;

            void Init() override;

            void Draw() override;

            Actor* GetRoot() const;

            void SetRoot(Actor* root);

            Camera* GetCamera() const;

            void SetCamera(Camera* camera);

    };

} /* namespace ThreeEngine */

#endif //THREEENGINE_SCENEGRAPH_H
