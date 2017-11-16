/*
 * File CameraController.cpp in project ThreeEngine
 *
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "SphereCameraController.h"
#include "../Camera/Ortho.h"
#include "../Camera/Perspective.h"

namespace ThreeEngine {

    SphereCameraController::SphereCameraController() :
            engine(Engine::Instance()),
            inPerspective(true),
            previousMouseLocation(),
            yawPitch(),
            translation(Matrix::IdentityMatrix()),
            rotation(Matrix::IdentityMatrix()),
            quat(), camera(nullptr) { }

    SphereCameraController::~SphereCameraController() = default;

    void SphereCameraController::Update() {
        if (!engine || !camera) {
            return;
        }

        // Toggle between Ortho and Perspective
        if (engine->input.Click('p')) {
            if (inPerspective) {
                camera->SetProjection(new Ortho(-10, 10, -10, 10, 1, 100));
                inPerspective = false;
            } else {
                number width = engine->config["window"]["x"];
                number height = engine->config["window"]["y"];
                number aspect = width / height;
                camera->SetProjection(new Perspective(30, aspect, 1, 100));
                inPerspective = true;
            }
        }

        // Check if mouse was clicked
        if (engine->input[MouseKeys::LEFT] || engine->input[MouseKeys::RIGHT]) {
            Vector2 delta = LockMouse();

            float sensitivity = Time::Delta() / 500.0f;
            delta *= sensitivity;
            delta.Y = -delta.Y;

            // Always calculate the updated quaternion to even if it is not being used
            // otherwise it will break the toggling.
            quat = (Quat::FromAngleAxis(delta.X, Vector(0, 1, 0)) *
                    Quat::FromAngleAxis(-delta.Y,
                                        Vector(1, 0, 0))).Normalize() * quat;

            camera->SetView(Matrix::TranslationMatrix(Vector(0, 0, -30)) *
                            quat.ToMatrix());
        } else {
            UnlockMouse();
        }

    }

    Vector2 SphereCameraController::LockMouse() {
        engine->input.SetMouseCursor(MouseCursor::CURSOR_NONE);
        const Vector2 mouse = engine->input.GetMouseScreenLocation();

        Vector2 delta = {(mouse.X - previousMouseLocation.X),
                         (mouse.Y - previousMouseLocation.Y)};

        // check if mouse is at window borders
        bool mouseXUpdate =
                (mouse.X <= 0) ||
                (mouse.X >= (int) engine->config["window"]["x"] - 1);
        bool mouseYUpdate =
                (mouse.Y <= 0) ||
                (mouse.Y >= (int) engine->config["window"]["y"] - 1);

        if (mouseXUpdate || mouseYUpdate) {
            Vector2 newMouseLoc = mouse;

            if (mouseXUpdate) {
                newMouseLoc.X = (number) engine->config["window"]["x"] / 2;
                previousMouseLocation.X = newMouseLoc.X - delta.X;
            }

            if (mouseYUpdate) {
                newMouseLoc.Y = (number) engine->config["window"]["y"] / 2;
                previousMouseLocation.Y = newMouseLoc.Y - delta.Y;
            }

            engine->input.SetMouseScreenLocation(
                    static_cast<int>(newMouseLoc.X),
                    static_cast<int>(newMouseLoc.Y));
        } else {
            previousMouseLocation = mouse;
        }

        return delta;
    }

    void SphereCameraController::UnlockMouse() {
        engine->input.SetMouseCursor(MouseCursor::CURSOR_INHERIT);
        previousMouseLocation = engine->input.GetMouseScreenLocation();
    }

} /* namespace Divisaction */