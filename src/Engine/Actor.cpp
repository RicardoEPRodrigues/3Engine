/*
 * File Actor.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include <GL/glew.h>
#include "Actor.h"
#include "OpenGLUtils.h"

namespace ThreeEngine {

    Actor::Actor() : IDrawable(), mesh(), shaderProgram(nullptr),
                    transform({Vector(0), Quat(), Vector(1)}) { }

    Actor::~Actor() = default;

    void Actor::Init() {
        if (!shaderProgram) {
            shaderProgram = std::make_shared<ShaderProgram>(
                    "shaders/Default/program.json");
        }
        shaderProgram->Init();
        mesh.Init();
    }

    void Actor::Draw() {
        mesh.Bind();
        shaderProgram->Bind();

        number matrixArray[16];
        (Matrix::TranslationMatrix(transform.translation) *
            transform.rotation.ToMatrix() *
            Matrix::ScaleMatrix(transform.scale)).ToArray(matrixArray);
        glUniformMatrix4fv(shaderProgram->GetUniformLocationId("ModelMatrix"),
                           1, GL_FALSE,
                           matrixArray);
        if (preDraw) {
            preDraw();
        }
        mesh.Draw();
        if (postDraw) {
            postDraw();
        }

        shaderProgram->Unbind();
        mesh.Unbind();

        CheckOpenGLError("Could not draw Actor.");
    }

} // namespace ThreeEngine