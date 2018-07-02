/*
 * File Camera.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "Camera.h"
#include "../OpenGLUtils.h"
#include "LookAt.h"
#include "Perspective.h"

namespace ThreeEngine {

    Camera::Camera() : Camera(0) { }

    Camera::Camera(GLuint uniformBlockBidingID) : Camera(uniformBlockBidingID,
                                                         new Perspective(30, 640.0f / 480.0f, 1,
                                                                         10),
                                                         new LookAt({5, 5, 5}, {0, 0, 0},
                                                                    {0, 1, 0})) { }

    Camera::Camera(GLuint uniformBlockBidingID, Matrix* projection, Matrix* view)
            : projection(projection), view(view), uniformBlockBidingID(uniformBlockBidingID) { }

    Camera::~Camera() {
        glDeleteBuffers(1, &vboId);

        delete projection;
        delete view;
    }

    void Camera::Init() {
        glGenBuffers(1, &vboId);
        glBindBuffer(GL_UNIFORM_BUFFER, vboId);
        glBufferData(GL_UNIFORM_BUFFER, sizeof(glMatrix) * 2, nullptr, GL_STREAM_DRAW);
        glBindBufferBase(GL_UNIFORM_BUFFER, uniformBlockBidingID, vboId);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
        CheckOpenGLError("Could not create VAOs and VBOs.");
    }

    void Camera::Draw() {
        glBindBuffer(GL_UNIFORM_BUFFER, vboId);
        number viewMatrix[16];
        (transform * (*view)).ToArray(viewMatrix);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Matrix), viewMatrix);
        number projectionMatrix[16];
        projection->ToArray(projectionMatrix);
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(Matrix), sizeof(Matrix), projectionMatrix);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
        CheckOpenGLError("Could not draw camera.");
    }

    Matrix* Camera::getProjection() const {
        return projection;
    }

    void Camera::SetProjection(Matrix* projection) {
        if (this->projection == projection) {
            return;
        }
        delete this->projection;
        this->projection = projection;
    }

    void Camera::SetProjection(Matrix const& projection) {
        if (!this->projection) {
            return;
        }
        *this->projection = projection;
    }

    Matrix* Camera::GetView() const {
        return view;
    }

    void Camera::SetView(Matrix* view) {
        if (this->view == view) {
            return;
        }
        delete this->view;
        this->view = view;
    }

    void Camera::SetView(Matrix const& view) {
        if (!this->view) {
            return;
        }
        *this->view = view;
    }
} /* namespace Divisaction */