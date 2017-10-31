/*
 * File CameraController.cpp in project ThreeEngine
 *
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "CameraController.h"
#include "../../Engine/Camera/Ortho.h"
#include "../../Engine/Camera/Perspective.h"
#include "../../Engine/Camera/LookAt.h"

namespace ThreeEngine {

    CameraController::CameraController() : inPerspective(true), previousMouseLocation(), yawPitch(),
        translation(Matrix::IdentityMatrix()),
        rotation(Matrix::IdentityMatrix()) {
        engine = Engine::Instance();
    }

    CameraController::~CameraController() = default;

    void CameraController::Update() {
        if (engine) {
            const Vector2 mouse = engine->input.GetMouseScreenLocation();
            Camera* camera = engine->camera;

            if (engine->input.Click('p')) {
                if (inPerspective) {
                    camera->SetProjection(new Ortho(-2, 2, -2, 2, 1, 100));
                    inPerspective = false;
                }
                else {
                    number width = engine->config["window"]["x"];
                    number height = engine->config["window"]["y"];
                    number aspect = width / height;
                    camera->SetProjection(new Perspective(30, aspect, 1, 100));
                    inPerspective = true;
                }
            }

            auto lookAt = static_cast<LookAt*>(camera->GetView());

            if (engine->input['w'] || engine->input[SpecialKeys::UP_KEY]) {
                //                translation = Matrix::TranslationMatrix({0, 0, 0.1f, 0}) * translation;

                Vector delta = (lookAt->v) * 0.05f;
                lookAt->eye += delta;
            }

            if (engine->input['s'] || engine->input[SpecialKeys::DOWN_KEY]) {
                //                translation = Matrix::TranslationMatrix({0, 0, -0.1f, 0}) * translation;

                Vector delta = -lookAt->v * 0.05f;
                lookAt->eye += delta;
            }

            if (engine->input['d'] || engine->input[SpecialKeys::RIGHT_KEY]) {
                //                translation = Matrix::TranslationMatrix({-0.1f, 0, 0, 0}) * translation;

                Vector delta = lookAt->s * 0.05f;
                lookAt->eye += delta;
            }

            if (engine->input['a'] || engine->input[SpecialKeys::LEFT_KEY]) {
                //                translation = Matrix::TranslationMatrix({0.1f, 0, 0, 0}) * translation;

                Vector delta = -lookAt->s * 0.05f;
                lookAt->eye += delta;
            }

            if (engine->input['q']) {
                //                translation = Matrix::TranslationMatrix({0, -0.1f, 0, 0}) * translation;

                Vector delta = -lookAt->u * 0.05f;
                lookAt->eye += delta;
            }

            if (engine->input['e']) {
                //                translation = Matrix::TranslationMatrix({0, 0.1f, 0, 0}) * translation;
                Vector delta = lookAt->u * 0.05f;
                lookAt->eye += delta;
                lookAt->center += delta;
            }

            if (engine->input[MouseKeys::LEFT] || engine->input[MouseKeys::RIGHT]) {
                float sensitivity = 0.05f;
                Vector2 delta = { (mouse.X - previousMouseLocation.X) * sensitivity,
                                 (previousMouseLocation.Y - mouse.Y) * sensitivity };

                Matrix rotation = Matrix(Matrix3::RotationMatrix(lookAt->u, -delta.X)) *
                    Matrix(Matrix3::RotationMatrix(lookAt->s, delta.Y));
                lookAt->v = rotation * Vector4(lookAt->v);
                lookAt->s = rotation * Vector4(lookAt->s);
                lookAt->u = lookAt->s ^lookAt->v;
            }
            lookAt->SetM(lookAt->eye, lookAt->v, lookAt->s, lookAt->u);

            previousMouseLocation = mouse;
        }

    }

} /* namespace Divisaction */