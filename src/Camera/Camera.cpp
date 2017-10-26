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

//    const glMatrix I = {
//            1.0f, 0.0f, 0.0f, 0.0f,
//            0.0f, 1.0f, 0.0f, 0.0f,
//            0.0f, 0.0f, 1.0f, 0.0f,
//            0.0f, 0.0f, 0.0f, 1.0f
//    };
//
//    const glMatrix ModelMatrix = {
//            1.0f, 0.0f, 0.0f, 0.0f,
//            0.0f, 1.0f, 0.0f, 0.0f,
//            0.0f, 0.0f, 1.0f, 0.0f,
//            -0.5f, -0.5f, -0.5f, 1.0f
//    }; // Column Major
//
// // Eye(5,5,5) Center(0,0,0) Up(0,1,0)
//    const glMatrix ViewMatrix1 = {
//            0.70f, -0.41f, 0.58f, 0.00f,
//            0.00f, 0.82f, 0.58f, 0.00f,
//            -0.70f, -0.41f, 0.58f, 0.00f,
//            0.00f, 0.00f, -8.70f, 1.00f
//    }; // Column Major
//
// // Eye(-5,-5,-5) Center(0,0,0) Up(0,1,0)
//    const glMatrix ViewMatrix2 = {
//            -0.70f, -0.41f, -0.58f, 0.00f,
//            0.00f, 0.82f, -0.58f, 0.00f,
//            0.70f, -0.41f, -0.58f, 0.00f,
//            0.00f, 0.00f, -8.70f, 1.00f
//    }; // Column Major
//
// // Orthographic LeftRight(-2,2) TopBottom(-2,2) NearFar(1,10)
//    const glMatrix ProjectionMatrix1 = {
//            0.50f, 0.00f, 0.00f, 0.00f,
//            0.00f, 0.50f, 0.00f, 0.00f,
//            0.00f, 0.00f, -0.22f, 0.00f,
//            0.00f, 0.00f, -1.22f, 1.00f
//    }; // Column Major
//
// // Perspective Fovy(30) Aspect(640/480) NearZ(1) FarZ(10)
//    const glMatrix ProjectionMatrix2 = {
//            2.79f, 0.00f, 0.00f, 0.00f,
//            0.00f, 3.73f, 0.00f, 0.00f,
//            0.00f, 0.00f, -1.22f, -1.00f,
//            0.00f, 0.00f, -2.22f, 0.00f
//    }; // Column Majors

    Camera::Camera() : Camera(0) { }

    Camera::Camera(GLuint uniformBlockBidingID) : Camera(uniformBlockBidingID,
                                                         new Perspective(30, 640.0f / 480.0f, 1,
                                                                         10),
                                                         new LookAt({5, 5, 5}, {0, 0, 0},
                                                                    {0, 1, 0})) { }

    Camera::Camera(GLuint uniformBlockBidingID, Matrix* projection, Matrix* view)
            : uniformBlockBidingID(uniformBlockBidingID), projection(projection), view(view) { }

    Camera::~Camera() {
        glDeleteBuffers(1, &vboId);

        delete projection;
        delete view;
    }

    void Camera::Init() {
        glGenVertexArrays(1, &vaoId);
        glBindVertexArray(vaoId);
        {
            glGenBuffers(1, &vboId);
            glBindBuffer(GL_UNIFORM_BUFFER, vboId);
            glBufferData(GL_UNIFORM_BUFFER, sizeof(glMatrix) * 2, 0, GL_STREAM_DRAW);
            glBindBufferBase(GL_UNIFORM_BUFFER, uniformBlockBidingID, vboId);
        }
        glBindVertexArray(0);
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
} /* namespace Divisaction */