/*
 * File Actor.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include <GL/glew.h>
#include "Actor.h"
#include "OpenGLUtils.h"

namespace ThreeEngine {

    Actor::Actor() : IDrawable(), mesh(), shaderProgram(nullptr) { }

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
        transform.ToArray(matrixArray);
        glUniformMatrix4fv(shaderProgram->GetUniformLocationId("ModelMatrix"),
                           1, GL_FALSE,
                           matrixArray);
        mesh.Draw();

        shaderProgram->Unbind();
        mesh.Unbind();

        CheckOpenGLError("Could not draw Actor.");
    }

} // namespace ThreeEngine