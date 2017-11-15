/*
 * File Actor.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include <GL/glew.h>
#include "Actor.h"
#include "OpenGLUtils.h"

namespace ThreeEngine {

    Actor::Actor()
            : IDrawable(), isInitiated(false), transform(), mesh(nullptr),
              shaderProgram(nullptr), parent(nullptr) { }

    Actor::~Actor() {
        for (auto&& child : children) {
            delete child;
        }
    }

    void Actor::Init() {
        if (isInitiated) {
            return;
        }
        isInitiated = true;
        if (!GetShaderProgram()) {
            shaderProgram = std::make_shared<ShaderProgram>(
                    "shaders/Default/program.json");
        }
        GetShaderProgram()->Init();
        if (mesh) {
            mesh->Init();
        }
        for (auto&& child : children) {
            child->Init();
        }
    }

    void Actor::Draw() {
        if (mesh) { // Actor Mesh
            mesh->Bind();
            GetShaderProgram()->Bind();

            number matrixArray[16];
            GetModelMatrix().ToArray(matrixArray);
            glUniformMatrix4fv(
                    GetShaderProgram()->GetUniformLocationId("ModelMatrix"),
                    1, GL_FALSE,
                    matrixArray);
            if (preDraw) {
                preDraw();
            }
            mesh->Draw();
            if (postDraw) {
                postDraw();
            }

            GetShaderProgram()->Unbind();
            mesh->Unbind();

            CheckOpenGLError("Could not draw Actor.");
        }
        // Children
        for (auto&& child : children) {
            child->Draw();
        }
    }

    Matrix Actor::GetModelMatrix() {
        return GetParentModelMatrix() * GetLocalModelMatrix();
    }

    Matrix Actor::GetLocalModelMatrix() {
        return Matrix::TranslationMatrix(transform.translation) *
               transform.rotation.ToMatrix() *
               Matrix::ScaleMatrix(transform.scale);
    }

    Matrix Actor::GetParentModelMatrix() {
        if (!parent) {
            return Matrix::IdentityMatrix();
        }
        return parent->GetParentModelMatrix() * parent->GetModelMatrix();
    }

    std::shared_ptr<ShaderProgram> Actor::GetShaderProgram() {
        if (shaderProgram) {
            return shaderProgram;
        }
        if (parent) {
            return parent->GetShaderProgram();
        }
        return nullptr;
    }

    void Actor::SetParent(Actor* parent) {
        Actor::parent = parent;
        if (Actor::parent) {
            Actor::parent->children.push_back(this);
        }
    }

} // namespace ThreeEngine