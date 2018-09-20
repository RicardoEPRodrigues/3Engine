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
            : IDrawable(), shaderProgram(nullptr), isInitiated(false),
              transform(), mesh(nullptr), textures(), parent(nullptr),
              children() { }

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
        for (auto&& texture : textures) {
            texture->Init();
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

            for (auto&& texture : textures) {
                texture->Draw();
            }

            if (preDraw) {
                preDraw();
                CheckOpenGLError("Error while on Pre Draw.");
            }
            mesh->Draw();
            if (postDraw) {
                postDraw();
                CheckOpenGLError("Error while on Post Draw.");
            }

            for (auto&& texture : textures) {
                texture->Unbind();
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
        auto local = GetLocalModelMatrix();
        auto parent = GetParentModelMatrix();
        return parent * local;
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
        return parent->GetModelMatrix();
    }

    void Actor::setShaderProgram(
            const std::shared_ptr<ShaderProgram>& shaderProgram) {
        Actor::shaderProgram = shaderProgram;
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