/*
 * File Actor.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_ACTOR_H
#define THREEENGINE_ACTOR_H

#include "IDrawable.h"
#include "Math/Quat.h"
#include "Shapes/Mesh.h"
#include "Shader/ShaderProgram.h"

namespace ThreeEngine {
    class Actor : public IDrawable {
        public:
            struct Transform {
                Vector translation;
                Quat rotation;
                Vector scale;
            };

            Transform transform;

            std::function<void()> preDraw, postDraw;

            Mesh mesh;

            std::shared_ptr<ShaderProgram> shaderProgram;

            Actor();

            ~Actor() override;

            void Init() override;

            void Draw() override;
    };
} // namespace ThreeEngine

#endif //THREEENGINE_ACTOR_H
