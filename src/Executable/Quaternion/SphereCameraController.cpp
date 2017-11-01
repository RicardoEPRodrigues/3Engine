/*
 * File CameraController.cpp in project ThreeEngine
 *
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include <Engine/OpenGLUtils.h>
#include "SphereCameraController.h"
#include "Engine/Camera/Ortho.h"
#include "Engine/Camera/Perspective.h"

namespace ThreeEngine {

    SphereCameraController::SphereCameraController() : engine(Engine::Instance()),
                                                       inPerspective(true),
                                                       useQuat(true), previousMouseLocation(),
                                                       yawPitch(),
                                                       translation(Matrix::IdentityMatrix()),
                                                       rotation(Matrix::IdentityMatrix()),
                                                       quat({1, 0, 0, 0}) { }

    SphereCameraController::~SphereCameraController() = default;

    void SphereCameraController::Update() {
        if (engine) {
            const Vector2 mouse = engine->input.GetMouseScreenLocation();
            Camera* camera = engine->camera;

            // Toggle between Ortho and Perspective
            if (engine->input.Click('p')) {
                if (inPerspective) {
                    camera->SetProjection(new Ortho(-2, 2, -2, 2, 1, 100));
                    inPerspective = false;
                } else {
                    number width = engine->config["window"]["x"];
                    number height = engine->config["window"]["y"];
                    number aspect = width / height;
                    camera->SetProjection(new Perspective(30, aspect, 1, 100));
                    inPerspective = true;
                }
            }
            // Toggle between using Quaternions or Euler Angles for rotations
            if (engine->input.Click('g')) {
                useQuat = !useQuat;
            }

            // Check if mouse was clicked
            if (engine->input[MouseKeys::LEFT] || engine->input[MouseKeys::RIGHT]) {
                engine->input.SetMouseCursor(MouseCursor::CURSOR_NONE);

                float sensitivity = Time::Delta() / 500.0f;
                Vector2 delta = {(mouse.X - previousMouseLocation.X) * sensitivity,
                                 (previousMouseLocation.Y - mouse.Y) * sensitivity};

                // Always calculate the updated quaternion to even if it is not being used
                // otherwise it will break the toggling.
                quat = (Quat::FromAngleAxis(delta.X, Vector(0, 1, 0)) *
                        Quat::FromAngleAxis(-delta.Y, Vector(1, 0, 0))).Normalize() * quat;

                if (useQuat) {
                    camera->SetView(Matrix::TranslationMatrix(Vector(0, 0, -10)) * quat.ToMatrix());
                } else {

                    Matrix rotation = Matrix(Matrix3::RotationMatrix(Maths::Axis::Y, -delta.X)) *
                                      Matrix(Matrix3::RotationMatrix(Maths::Axis::X, -delta.Y));
                    camera->SetView(*camera->GetView() * rotation);
                }


                // check if mouse is at window borders
                bool mouseXUpdate =
                        (mouse.X <= 0) || (mouse.X >= (int) engine->config["window"]["x"]);
                bool mouseYUpdate =
                        (mouse.Y <= 0) || (mouse.Y >= (int) engine->config["window"]["y"]);

                if (mouseXUpdate || mouseYUpdate) {
                    Vector2 newMouseLoc = mouse;

                    if (mouseXUpdate) {
                        newMouseLoc.X = (int) engine->config["window"]["x"] / 2;
                        previousMouseLocation.X = newMouseLoc.X - delta.X;
                    }

                    if (mouseYUpdate) {
                        newMouseLoc.Y = (int) engine->config["window"]["y"] / 2;
                        previousMouseLocation.Y = newMouseLoc.Y - delta.Y;
                    }

                    engine->input.SetMouseScreenLocation(static_cast<int>(newMouseLoc.X),
                                                         static_cast<int>(newMouseLoc.Y));
                } else {
                    previousMouseLocation = mouse;
                }
            } else {
                engine->input.SetMouseCursor(MouseCursor::CURSOR_INHERIT);
                previousMouseLocation = mouse;
            }

        }

    }

} /* namespace Divisaction */