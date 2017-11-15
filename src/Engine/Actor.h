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
        private:
            bool isInitiated;

            Matrix GetModelMatrix();
            Matrix GetLocalModelMatrix();
            Matrix GetParentModelMatrix();

            std::shared_ptr<ShaderProgram> GetShaderProgram();
        public:
            struct Transform {
                Vector translation{0};
                Quat rotation{};
                Vector scale{1};
            };

            Transform transform;

            std::function<void()> preDraw, postDraw;

            Mesh mesh;

            std::shared_ptr<ShaderProgram> shaderProgram;

            Actor* parent;

            std::vector<Actor*> children;

            Actor();

            ~Actor() override;

            void Init() override;

            void Draw() override;

            void SetParent(Actor* parent);
    };
} // namespace ThreeEngine

#endif //THREEENGINE_ACTOR_H
