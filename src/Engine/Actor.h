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
#include "Engine/Shader/Texture.h"

namespace ThreeEngine {
    class Actor : public IDrawable {
        private:

            std::shared_ptr<ShaderProgram> shaderProgram;

        protected:
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

            std::shared_ptr<Mesh> mesh;

            std::vector<std::shared_ptr<ITexture>> textures;

            Actor* parent;

            std::vector<Actor*> children;

            Actor();

            ~Actor() override;

            void Init() override;

            void Draw() override;

            void SetParent(Actor* parent);

            void setShaderProgram(
                    const std::shared_ptr<ShaderProgram>& shaderProgram);
    };
} // namespace ThreeEngine

#endif //THREEENGINE_ACTOR_H
