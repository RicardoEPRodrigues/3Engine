/*
 * File CameraController.cpp in project ThreeEngine
 *
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "CameraControllerRot.h"
#include "../../Engine/Camera/Ortho.h"
#include "../../Engine/Camera/Perspective.h"

namespace ThreeEngine {

    CameraControllerRot::CameraControllerRot() : engine(Engine::Instance()), inPerspective(true),
                                                 useQuat(false), previousMouseLocation(),
                                                 yawPitch(), translation(Matrix::IdentityMatrix()),
                                                 rotation(Matrix::IdentityMatrix()),
                                                 quat({1, 0, 0, 0}) { }

    CameraControllerRot::~CameraControllerRot() = default;

    void CameraControllerRot::Update() {
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

            if (engine->input[MouseKeys::LEFT] || engine->input[MouseKeys::RIGHT]) {
                float sensitivity = 0.05f;
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
            }

            previousMouseLocation = mouse;
        }

    }

} /* namespace Divisaction */