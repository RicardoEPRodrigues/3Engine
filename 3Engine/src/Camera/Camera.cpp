/*
 * File Camera.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "Camera.h"
#include "../OpenGLUtils.h"
#include "LookAt.h"

namespace ThreeEngine {

    Camera::Camera() : Camera(0) {}

    Camera::Camera(GLuint uniformBlockBidingID)
            : Camera(uniformBlockBidingID,
                     new Matrix(Matrix::PerspectiveMatrix(30, 640.0f / 480.0f, 1, 10)),
                     new LookAt({5, 5, 5}, {0, 0, 0},
                                {0, 1, 0})) {}

    Camera::Camera(GLuint uniformBlockBidingID, Matrix* projection, Matrix* view)
            : projection(projection), view(view), uniformBlockBidingID(uniformBlockBidingID) {}

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
        (*view).ToArray(viewMatrix);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(viewMatrix), viewMatrix);
        number projectionMatrix[16];
        projection->ToArray(projectionMatrix);
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(viewMatrix), sizeof(projectionMatrix),
                        projectionMatrix);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
        CheckOpenGLError("Could not draw camera.");
    }

    Matrix* Camera::getProjection() const {
        return projection;
    }

    void Camera::SetProjection(Matrix* matrix) {
        if (this->projection == matrix) {
            return;
        }
        delete this->projection;
        this->projection = matrix;
    }

    void Camera::SetProjection(Matrix const& matrix) {
        if (!this->projection) {
            return;
        }
        *this->projection = matrix;
    }

    Matrix* Camera::GetView() const {
        return view;
    }

    void Camera::SetView(Matrix* matrix) {
        if (this->view == matrix) {
            return;
        }
        delete this->view;
        this->view = matrix;
    }

    void Camera::SetView(Matrix const& matrix) {
        if (!this->view) {
            return;
        }
        *this->view = matrix;
    }
} /* namespace Divisaction */